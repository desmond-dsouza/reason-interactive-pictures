type person = {
  base_mood: int,
  mood_swing: int
};

let initialPerson = {base_mood: 120, mood_swing: 0};

let updatePerson t {base_mood, mood_swing} => {
  let delta = 120. *. sin (t /. 250.) |> int_of_float;
  {base_mood, mood_swing: delta}
};

let showPerson {base_mood, mood_swing} => {
  let mood = base_mood + mood_swing;
  let color = Picture.Rgb mood 100 100;
  let r = 10 + mood;
  Picture.picture (600, 600) [Picture.Circle (250, 260) r color]
};

let main: Picture.display Interaction.msg =
  Interaction.simulate initialPerson showPerson updatePerson delta_ms::20.0;
