modded class PlayerBase extends ManBase
{
	override void OnConnect()
	{
		super.OnConnect();
		GetGame().ChatPlayer(5,this.ToString()+"A new player joined the server");
	}
}
