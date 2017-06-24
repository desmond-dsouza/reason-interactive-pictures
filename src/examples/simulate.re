type person = {
  base_mood: int,
  mood_swing: int,
  shift: int
};

let initialPerson = {base_mood: 120, mood_swing: 0, shift: 0};

let updatePerson t (p: person) => {
  let delta = 120. *. sin (t /. 250.) |> int_of_float;
  {...p, mood_swing: delta}
};

let showPerson {base_mood, mood_swing, shift} => {
  let mood = base_mood + mood_swing;
  let color = Picture.Rgb mood 100 100;
  let r = 10 + mood;
  Picture.picture (1000, 600) [Picture.Circle (250 + shift, 260) r color]
};

let main: Picture.simpleDisplay =
  Interaction.simulate initialPerson showPerson updatePerson delta_ms::20.0;
