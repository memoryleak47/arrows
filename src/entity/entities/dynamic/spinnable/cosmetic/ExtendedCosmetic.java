package entity.entities.dynamic.spinnable.cosmetic;

import entity.entities.dynamic.SpinnableEntity;
import graphics.Animation;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class ExtendedCosmetic extends SpinnableEntity
{
	public ExtendedCosmetic(GamePosition position, Animation animation)
	{
		super(position, animation);
	}
}