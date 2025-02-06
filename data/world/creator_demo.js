const locID = "<location-id/>";
// NOTE: all parameters that end with 'Diag' will be in the format [<what to print out to the user>, <a lua script to run>]
//       if any are left blank the boilerplate code lua will not be inserted

class Location {
	constructor() {
		this._name = null;
		this._layout = null;
		this._objects = [];
		this._transitions = [];
	}
	// GETTERS
	get name() {
		return this._name;
	}
	
	get layout() {
		return this._layout;
	}
	
	get objects() {
		return this._objects;
	}
	
	get transitions() {
		return this._transitions;
	}
	// SETTERS
	set name(v) {
		this._name = v;
	}
	
	set layout(v) {
		this._layout = v;
	}
	
	void objects(v) {
		// v is a array OR a single value
		this._objects.push(v);
	}
	
	// CHECK VALIDITY FUNCTION
	_check: function() {
		
	}
}

class GameObject {
	
}

// class InteractionScript
// Used for making the user roll for a value
// The dialouges will stack as well, so if a raise is rolled,
//  it will print to the user all three of the notices, but only run
//  the raise lua function
function NoticeRoller(ifFailDiag, ifSuccessDiag, ifRaiseDiag) {
}

// function InteractionScript
// Used for scripts that will return input back to the user
function InteractionScript(luaFunction, ifTrueDiag, ifFalseDiag) {
	
}

// function SwitchScript
// Used for scripts that will return a lot of data back to the user
function SwitchScript(luaFunction, ...ifNDiag) {
	
}

// function NullScript
// A blank lua script
function NullScript() {
	
}

// function RawScript
// A no-nonsense lua script
function RawScript(luaScript) {
	
}

// function TransitionScript
// Used for script that will move a player to another location
function TransitionScript(locationID, luaConditional, transitionDiag) {
	
}

class World {
	function create(locationID, initFunction) {
		let currentLocation = new Location();
		currentLocation.init = initFunction;
		currentLocation
	}
}


// START OF WORLD FILE

var world = new World();

var ActOne = {}

ActOne.ForestClearing = new Location(world);
ActOne.TownCenter = new Location(world);

ActOne.ForestClearing.init = function() {
		this.name = "Forest Clearing";
		this.layout = new BlankLocMatrix(10, 10);
		// this will tell the game to make sure these flags exist before the location
		// is even loaded, and if they dont it will set them to the default value
		this.flags = [
			[this.id + "stoneDoor", "false"]
		]
		// events are checked in C++ with predefined event triggers that run Lua scripts
		this.events = [
			Event("OnLoad", ``),
			Event("PlayerPos(5, 6)")
		];
		// scripts are written in Lua and are compiled once the user enters a location, then run every loop
		this.scripts = [
			``
		];
		this.objects([
			new GameObject(
				position=this.layout.pos(2, 2),
				character=ConditionalScript(`flag('${this.id}.stoneDoor')`, '/', '\\'),
				name="Rusty Lever",
				properties=[GameObject.Walkable, GameObject.Range(0)],
				description=NoticeRoller(
					["The lever is old and a little rotten, but it should still move.", ""],
					["It looks like it is used to move something heavy.", ""],
					["Looking a bit harder, you also notice a set of gears and axles from the lever to a big stone slab in the wall.", ""]
				),
				use=InteractionScript(`flag('${this.id}.stoneDoor', true)`,
					["The large stone slab on the far end of the room opens", ""],
					["The large stone slab on the far end of the room slams closed", ""]
				)
			),
			new GameObject(
				position=this.layout.pos(0, 5),
				properties=[GameObject.Transition],
				name="Stone Slab",
				description=NoticeRoller(
					["The door looks large and heavy.", ""],
					["It almost looks partially mechanical.", ""],
					["Looking a bit harder, you notice a axle running along the ground to a nearby lever.", ""]
				),
				use=TransitionScript(ActOne.TownCenter, `flag('${this.id}.stoneDoor')`)
			)
		])
	}
}


ActOne.TownCenter.init = function() {
		this.name = "Town Center";
		this.layout = new LocMatrix([
			[" ", " ", " ", " ", " ", " ", " ", " "],
			[" ", " ", " ", " ", " ", " ", " ", " "],
			[" ", " ", " ", " ", " ", " ", " ", " "],
			[" ", " ", " ", " ", " ", " ", " ", " "],
			[" ", " ", " ", " ", " ", " ", " ", " "],
			[" ", " ", " ", " ", " ", "#", "#", "#"],
			[" ", " ", " ", " ", " ", "#", "#", "#"],
			[" ", " ", " ", " ", " ", "#", "#", "#"]
		]);
		this.addObject(
			new GameObject(
				position=this.layout.pos(2, 2),
				name="Rusty Lever",
				description=NoticeRoller(
					["The lever is old and a little rotten, but it should still move.", ""],
					["It looks like it is used to move something heavy.", ""],
					["Looking a bit harder, you also notice a set of gears and axles from the lever to a big stone slab in the wall.", ""]
				),
				use=InteractionScript(`game.toggleFlag('${this.id}.stoneDoor')`,
					["The large stone slab on the far end of the room opens", ""],
					["The large stone slab on the far end of the room slams closed", ""]
				)
			),
			new GameObject(
				position=this.layout.pos(2, 2, width=3, zIndex),
				name="Stone Slab",
				description=NoticeRoller(
					["The door looks large and heavy.", ""],
					["It almost looks partially mechanical.", ""],
					["Looking a bit harder, you notice a axle running along the ground to a nearby lever.", ""]
				),
				use=TransitionScript()
			)
		)
	}
}