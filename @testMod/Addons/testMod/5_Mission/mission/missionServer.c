modded class MissionServer
{
    void MissionServer()
    {
        GetRPCManager().AddRPC( "testMod", "MyFunction", this, SingeplayerExecutionType.Server );
    }
	
	void MyFunction(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if( type == CallType.Server)
        {
			ref array<Man> playersListWidget = new array<Man>;
			ref array<string> info = new array<string>;
			Man playerWidget;
			GetGame().GetPlayers(playersListWidget);
			
            Print( "[bulot]Server function called through RPC by " +sender.GetName()+" "+sender.GetPlainId()+" "+sender.ToString()+" "+sender.GetPlayerId().ToString());
			vector myPos;
			int i;
			for (i = 0; i < playersListWidget.Count(); ++i )//Need info about sender
			{
				playerWidget = playersListWidget[i];
				if(sender.GetName() == playerWidget.GetIdentity().GetName())//My player
				{
					myPos = playerWidget.GetPosition();
					Print( "[bulot]Sender Pos = " +myPos);
				}
			}
			
			for (i = 0; i < playersListWidget.Count(); ++i )//For each player, we need to calc all distance with sender
			{
				playerWidget = playersListWidget[i];
				vector playerPos = playerWidget.GetPosition();
				string PlayerName = playerWidget.GetIdentity().GetName();
				float distanceMeOther = vector.Distance(myPos,playerPos);
				Print( "[bulot]We insert Other player " +playerWidget.GetIdentity().GetName()+" because "+sender.GetPlainId()+"!="+playerWidget.GetIdentity().GetPlainId());
				info.Insert(PlayerName + " - " + distanceMeOther.ToString()+"m");
			}
			
			GetRPCManager().SendRPC("testMod", "MyFunction", new Param2< ref array<Man>, ref array<string> >(playersListWidget, info), true, sender);
        }
	}
	
	override void OnEvent(EventType eventTypeId, Param params) 
	{
		PlayerIdentity identity;
		PlayerBase player;
		
		switch(eventTypeId)
		{
	        case ClientReadyEventTypeID:
				ClientReadyEventParams readyParams;
				Class.CastTo(readyParams, params);
				
				identity = readyParams.param1;
				Class.CastTo(player, readyParams.param2);
				string test = "test";
				Print("[bulot]RPC call on OnEvent ");
				GetRPCManager().SendRPC("testMod", "MyFunction2", new Param, true, identity);
				GetRPCManager().SendRPC("testMod", "testFunction", new Param, true, identity);
	        break;
	    }
		super.OnEvent(eventTypeId,params);
	}
};