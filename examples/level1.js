
// Welcome to the example script for Level 1!

// When this script is loaded, `init()` is called first

function init()
{
	// Load entire map data for Map 1 and display it on the screen
	
	game.loadMap("map1.json");
	
	// Place the player at the map entrance
	
	player.place(24, 4);
	
	// Load a troll character and place it near the player
	
	var troll = new Character("troll.json");
	troll.place(24, 10);
	
	// Add a talk action to the troll
	
	troll.action(talk_to_troll);
	
	// Once this function is finished, the player is free to run around
	// and trigger script actions!
}


function talk_to_troll(troll)
{
	// Open a conversation box to begin talking with the troll
	
	troll.say("Rgahtaieimnnnhehhstengrm m.irir,ngctinrDStn?");
	
	// Allow the player to reply with predetermined dialogue choices
	
	var answer = player.choice("What?", "No!", "Hseeeitl da mw at aüer nt,ae!");
	
	// The return value of `player.choice` is the zero-indexed position
	// of the choice. For example, "What?" is 0, "No!" is 1, etc.
	
	if (answer == 0)
	{
		troll.say("ZchcaeadenaVhDüclälaLhte eaMestste nwsT cön ele!");
	}
	else if (answer == 1)
	{
		// Kill the player
		
		player.health(0);
	}
	else if (answer == 2)
	{
		// Load the pizza item from a file
		
		var pizza = new Item("pizza.json");
		
		// Give the player a pizza
		
		troll.give(pizza, 1);
	}
}

