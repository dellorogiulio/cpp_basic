# COFFEE MACHINE

This example wants to model a simple coffee machine.

We already have a valves and buttons vendor which provides us a library to interact with them. The header files can be found in
```
include/hardware_vendor
```
In particular:
- a `Valve` class which allows us to open and close a valve for a specific time after a given delay.
- a `Button` class which allows us to set a callback on the button press.

## Valve
We can think to have a rack on which we mount different valves. Each valve can be `modular` or `impulsive`:
- a modular valve which can be used to pour liquid.
- a impulsive valve which can be used to make an "impulsive" action (such as, setting a plastic cup).

A `Valve` class can be created specifying its position on an hypothetical valves rack and its type
```cpp
using namespace coffee_machine;
Valve<0, ValveType::modular> coffee_valve;
Valve<1, ValveType::impulsive> stick_valve;
```
Once you have a `Valve`, you can schedule an open by calling 
```cpp
coffee_valve.scheduleOpen(1, 2); // open_time, delay
```
and the valve schedules the job for you.

## Button
Similarly to valves, we could have a buttons rack.
A button has a label to display on the coffee machine.

A `Button` class can be created specifying its position on the rack and its label
```cpp
using namespace coffee_machine;
Button<0> tea_button;
```
Once you have a `Button`, you can schedule a callback which will be handled by the button itself once someone presses it:
```cpp
tea_button.onPressed([](){
	//callback
});
```


# Exercise One: Basic Model

You should try to create a `CoffeeMachine` class which allows us to make:
- a tea
- a coffee

The available hardware is:
- 2 modulating valves 
- 2 impulsive valves 
- 2 buttons

Make a beverage involves three steps:
1) set a plastic cup
2) pour all needed ingredients following the given recipe
3) put a plastic stick

The recipe for each beverage can be read from the `recipe.json` file which is something like this:
```json
{
	"coffee": [
		{
			"liquid": "coffee",
			"time [s]": "5"
		}
	],
	"tea": [
		{
			"liquid": "tea",
			"time [s]": "10"
		}
	],
	"hot milk": [
		{
			"liquid": "milk",
			"time [s]": "15"
		}
	],
	"cappuccino": [
		{
			"liquid": "coffee",
			"time [s]": "5"
		},
		{
			"liquid": "milk",
			"time [s]": "10"
		}
	]
}
```
Each object is a different recipe; for example, to make an _hot milk_ you should pour milk for _15s_. To make a _cappuccino_, you have to pour coffee for 5 seconds and **then** 10 seconds of milk.


You must follow the recipe.json, since it can be updated directly from the client.

# Exercise Two: Advanced Model

We need a class which allows us to make:
- a tea
- a coffee
- an hot milk
- a cappuccino

The available hardware is:
- 3 modulating valves 
- 2 impulsive valves 
- 4 buttons


# Exercise Three: Safety Model

We need a class which allows us to make:
- a tea
- a coffee

But must handle a safety glass which must be opened once the plastic stick is set into the cup. 

The available hardware is:
- 2 modulating valves 
- 3 impulsive valves 
- 2 buttons
