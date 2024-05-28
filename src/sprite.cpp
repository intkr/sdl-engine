#include "sprite.h"

Sprite::Sprite(std::string name, Texture* tex, Geometry& geo) : attribute(name), geometry(geo), texture(tex) {}

Sprite::~Sprite() {
	deleteGeometry();
}

void Sprite::deleteGeometry() {
	delete geometry.texRect;
	delete geometry.baseRect;
	delete geometry.modRect;
	delete geometry.hitbox;
}

bool operator==(const Sprite& other) const {
	return attribute.name == other.attribute.name;
}

void Sprite::reset() {
	resetTextureMods();
}

void Sprite::resetTextureMods() {
	// Reset texture opacity and tint color to its default (100%, white)
	SDL_SetTextureAlphaMod(texture, 255);
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void Sprite::applyAnimation(Animation* a) {
	a->animate(&geometry);
}

void Sprite::updateHitbox(Orientation o) {
	double entityAngle = o.angle;
	if (shouldSpriteBeRotated(entityAngle))
		calculateRotation(entityAngle);
	offsetHitbox(o);
}

bool Sprite::shouldSpriteBeRotated(double angle) {
	// If the sprite fills the whole screen,
	// or if the entity does not rotate, return false.
	return !(angle = 0 | geometry.dstRect == nullptr);
}

void Sprite::calculateRotation(double angle) {
	SDL_FRect* rect = geometry.modRect;
	// Get center of the relative position.
	SDL_FPoint center { rect.x + rect.w / 2, rect.y + rect.h / 2 };

	// Angle value of the entity, converted to radians.
	double angle_rad = angle * M_PI / 180;
	// Apply the rotation matrix to the center.
	SDL_FPoint rotatedCenter {
		center.x * cos(angle_rad) - center.y * sin(angle_rad),
		center.x * sin(angle_rad) + center.y * cos(angle_rad) };
	
	// Change the rect's x / y values to match the rotated center point
	rect.x = rotatedCenter.x - rect.w / 2;
	rect.y = rotatedCenter.y - rect.h / 2;
	
	// Finally, add the entity's angle value to the sprite's value.
	geometry.angle += angle;
}

void Sprite::offsetHitbox(EntityGeometry& entityGeometry) {
	SDL_FRect* hitbox = geometry.hitbox;
	SDL_FPoint& pos = entityGeometry.position;
	
	hitbox.x += pos.x;
	hitbox.y += pos.y;
}

void Sprite::render(Renderer* renderer) {
	renderer->renderTexture(texture, geometry);
}

bool Sprite::isPointInSprite(SDL_FPoint point) {
	// Checks the collision between a point and a sprite that may or may not be rotated.
	// Because the hitbox object itself can't be rotated,
	// the function rotates the point by the opposite amount of the sprite's rotation angle ("unrotate")
	// and checks the collision with it instead.

	SDL_FRect* modRect = geometry.modRect;
	if (modRect == nullptr) {
		// Hitbox is infinitely large, so the point always collide.
		return true;
	}
	
	// negative value of the sprite's rotation angle, converted to radians
	float negativeAngle = (-geometry.angle) * M_PI / 180;
	// Apply the rotation matrix to the point
	SDL_FPoint rotatedPoint {
		point.x * cos(negativeAngle) - point.y * sin(negativeAngle),
		point.x * sin(negativeAngle) + point.y * cos(negativeAngle) };
	
	// Check if the unrotated point is within the hitbox.
	return SDL_PointInFRect(&point, modRect);
}