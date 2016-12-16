	// --- ----- --- //

	Gladiator : GOLD
	21/11/16 : 16/12/16
	Groupe :

	Adrien BOURGOIS
	Bastien TECHE
	Antoine SIMON

	// --- ----- --- //

	Controls:

	Movement : WASD / Gamepad L-Stick
	Camera : Mouse / Gamepad R-Stick
	
	Attack : L-Mouse Button / B Gamepad Button
	Lock : R-Mouse Button / Gamepad DPad Up 
	Switch Target : Mouse Wheel / Gamepad DPad L/R / Gamepad Trigger L/R
	
	Interact (Recover Equipment) : E / X Gamepad Button

	Menu : Escape / P / Select Gamepad Button

	// --- ----- --- //

	Project Architecture :

	// --- ----- --- //

	Implemented and WIP Features w/ task distribution :

	Adrien BOURGOIS :
		
		HUD: 
			Displaying characters (AI / Player) health as 3D Widgets
			but Remove because it causes a crash
		
		Day and Night Cycle: 
			Day & Night Cycle w/ light shifting
		
		Sounds: 
			[...]

	Bastien TECHE:

		AI:
			Positionning: 
				Calculate a safe position compared to player 
				and recalculate a position with safe position compared to other safe position to AI
			
			Attack: 
				AIDirector use a timer for launch AI to attack the player
				Playing attack animation
				Collision check on appropriate animation frame
			
			Death:
				Play death animation
				Disable controls and collision
				Stop logic
			

		Animation:
			Movement BlendSpace including moving forward , backward and strafes

		EndGame:
			Display a menu with a text designates the winner
			button restart
			button quit

		[WIP] Networking:
			It's not operational

	Antoine SIMON:

		Player:
			Movements: 
				Character faces movement direction
			
			Attack: 
				Playing attack animation
				Collision check on appropriate animation frame

			Death:
				Play death animation
				Disable controls

		Camera:
			Avoid collisions w/ determined objects (AI & props)

		Visual FX:
			Blood particles on hammer hit w/ blood splats 
			Dust particles on footstep

		Lock System:
			Lock logic target (enemy facing player)
			Switch target
			Player faces locked target
			Circle movement around player (cf Known Bug & Issues)

		[WIP] Equipment Drop :
			 Random chance for characters (AI / Player) to drop equipment on hit 
			 Physicalization of dropped equipment -> thrown backward
			 Debuffs when missing equipments
			 Player equipment recovery when near enough and key pressed
			 [WIP] Enemies equipment recovery

	// --- ----- --- //

	Unimplemented Features:

	// --- ----- --- //

	Known Bug & Issues :
		
		Lock System:
			LR strafes lack of accuracy : stacking those errors lead to spiral movement instead of clean circle
			Switch target glitched w/ gamepad inputs due to axis mapping
		
		Equipment Drop:
			The IA Recovered the weapon too fast or put many time for go to pick

	// --- ----- --- //

		//	EOF	//

	// --- ----- --- //