void main()
{
	int player_index = getlocalvar("player");

	int key_hold = getplayerproperty(player_index,"keys");

	if(key_hold & openborconstant("FLAG_MOVELEFT"))
	{

		key_hold ^= openborconstant("FLAG_MOVELEFT");

		key_hold |= openborconstant("FLAG_MOVEDOWN");
	}

	changeplayerproperty(player_index,"keys",key_hold);
}