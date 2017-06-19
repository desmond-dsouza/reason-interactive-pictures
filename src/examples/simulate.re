type person = {mood: int};

let base_mood = 120;

let updatePerson t {mood: _mood} => {
  let delta = 120. *. sin (t /. 250.);
  let mood' = base_mood + int_of_float delta;
  {mood: mood'}
};

let showPerson {mood} => {
  let color = Picture.Rgb mood 100 100;
  let r = 10 + mood;
  Picture.picture (1000, 1000) [Picture.Circle (500, 500) r color]
};

let main: Picture.mainType =
  Interaction.simulate {mood: 120} showPerson updatePerson delta_ms::20.0;
