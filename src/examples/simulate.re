type person = Draw.person;

let initialPerson = Draw.initialPerson;

let showPerson = Draw.showPerson;

let updatePerson t (p: person) => {
  let delta = 120. *. sin (t /. 250.) |> int_of_float;
  {...p, Draw.mood_swing: delta}
};

let main: Picture.simpleDisplay =
  Interaction.simulate initialPerson showPerson updatePerson delta_ms::20.0;
