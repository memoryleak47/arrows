#ifndef __CIRCLEBODY_CLASS__
#define __CIRCLEBODY_CLASS__

class GameVector;
class CompressBuffer;
class GameRect;

#include "Body.hpp"
#include <string>
#include <misc/compress/Cid.hpp>

class CircleBody : public Body
{
	public:
		CircleBody(const GameVector& pos, float rad, const GameVector& speed=GameVector(0,0), float rot=0.f, float spin=0.f);
		CircleBody(CompressBuffer*);
		virtual ~CircleBody() {}

		// compress
		CID getCID() const override;
		std::string getCompressString() const override;

		virtual BodyType getBodyType() const override;

		virtual GameRect getWrapper(float timeLeft) const override;
		virtual bool isCollidingPoint(const GameVector&) const override;

		virtual const GameVector& getPosition() const override;
		virtual const GameVector getSize() const;
		virtual const GameVector& getSpeed() const override;
		virtual float getRotation() const override;
		virtual float getRadius() const;
		virtual float getSpin() const override;
		virtual GameRect getRenderGameRect() const override;
		virtual void setPosition(const GameVector&) override;
		virtual void setSpeed(const GameVector&) override;
		virtual void setRotation(float) override;
		virtual void setSpin(float) override;

		virtual float getLeft() const;
		virtual float getRight() const;
		virtual float getTop() const;
		virtual float getBot() const;

		virtual std::string toString() const override;

		virtual void setSpeedAt(const GameVector&, const GameVector& where) override; // where is a map-coordinate
		virtual void reactToCollision(float massshare, const GameVector& speed, const GameVector& collisionPoint) override;
	private:
		virtual void apply(const Body*) override;

		GameVector position;
		GameVector speed;
		float rotation;
		float radius;
		float spin;
};

#endif
