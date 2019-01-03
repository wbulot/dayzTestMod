modded class MissionGameplay
{
	void MissionGameplay()
	{
		GetRPCManager().AddRPC( "testMod", "testFunction", this, SingeplayerExecutionType.Client );
		Print("[bulot]Mission Gameplay");
	}
	
	void testFunction()
	{
		Print("[bulot]testFunction called by the server OnEvent");
		//UIScriptedMenu menu = GetUIManager().EnterScriptedMenu(9999, NULL);
		//menu.Init().Show(true);
		
		UIScriptedMenu menu = GetGame().GetUIManager().EnterScriptedMenu(9999,NULL);
	}
	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);

		if ( key == KeyCode.KC_P )
		{
			if (!GetUIManager().IsMenuOpen( 8888 ))
			{
				GetUIManager().EnterScriptedMenu(8888, NULL);
			}
		}
	}
	
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		if ( key == KeyCode.KC_P )
		{
			if ( GetUIManager().IsMenuOpen( 8888 ))
			{
				GetUIManager().CloseAll();
			}
		}
	}
};