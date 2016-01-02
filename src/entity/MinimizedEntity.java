package entity;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.game.Camera;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;

public abstract class MinimizedEntity implements java.io.Serializable
{
	private ImageID imageID;
	private GamePosition position;

	public MinimizedEntity(ImageID imageID, GamePosition position)
	{
		this.imageID = imageID;
		this.position = position;
	}

	public void render()
	{
		if (inScreen())
		{
			PixelPosition position = Camera.get().gamePositionToPixelPosition(new GamePosition(getPosition().minus(getSize().times(0.5f))));
			Screen.g().drawImage(ImageFile.getImageByImageID(getImageID()), position.getX(), position.getY(), null);
		}
	}

	// setter
	public void setImageID(ImageID imageID)
	{
		Debug.warnIf(imageID == null, "MinimizedEntity.setImageID(): imageID == null");
		this.imageID = imageID;
	}

	public void setPosition(GamePosition position)
	{
		Debug.warnIf(position == null, "MinimizedEntity.setPosition(): position == null");
		this.position = position;
	}

	// getter
	public ImageID getImageID()
	{
		Debug.warnIf(imageID == null, "MinimizedEntity.getImageID(): imageID == null");
		return imageID;
	}

	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "MinimizedEntity.getPosition(): position == null");
		return position;
	}

	public GameSize getSize()
	{
		Debug.warnIf(getImageID() == null, "MinimizedEntity.getSize(): getImageID is null");
		return new GameSize(getImageID());
	}

	private boolean inScreen()
	{
		// TODO
		return true;
	}
}
