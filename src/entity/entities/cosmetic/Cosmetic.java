package entity.entities.cosmetic;

import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class Cosmetic extends Entity
{
	public Cosmetic(GamePosition position, GameSize size, Animation animation)
	{
		super(position, size, animation);
	}
}
