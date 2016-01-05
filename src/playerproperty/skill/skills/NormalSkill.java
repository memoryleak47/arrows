package playerproperty.skill.skills;

import playerproperty.skill.Skill;

public abstract class NormalSkill extends Skill
{
	@Override public void onKeyPressed()
	{
		if (getCharge() == MAX_CHARGE)
		{
			trigger();
			onTrigger();
		}
	}

	@Override protected void onTrigger()
	{
		setCharge(0.0f);
	}

	@Override protected boolean isRecharging() // Solange man nicht komplett aufgeladen ist, weiter aufladen
	{
		return (getCharge() < MAX_CHARGE);
	}
}
