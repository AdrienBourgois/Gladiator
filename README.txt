	// --- ----- --- //

	Gladiator : BETA
	21/11/16 : 9/12/16
	Groupe :

	Adrien BOURGOIS
	Bastien TECHE
	Antoine SIMON

	// --- ----- --- //

	Controls:

	// --- ----- --- //

	Project Architecture :

	// --- ----- --- //

	Implemented and WIP Features w/ task distribution :

	Adrien BOURGOIS :
		
		HUD: 
			Displaying characters (AI / Player) health as 3D Widgets
		
		Day and Night Cycle: 
			Day & Night Cycle w/ light shifting
		
		Sounds: 
			[...]

	Bastien TECHE:

		AI:
			Positionning: 
				[...]
			
			Attack: 
				[...]
			
			Death:
				[...]

		Animation:
			Movement BlendSpace including moving forward , backward and strafes

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
			Blood particles on hammer hit
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

	// --- ----- --- //

		//	EOF	//

	// --- ----- --- //