type person = {mood: int};

let base_mood = 120;

let updatePerson t {mood} => {
  let delta = 120. *. sin (t /. 250.);
  let mood' = base_mood + int_of_float delta;
  {mood: mood'}
};

let showPerson {mood} => {
  let color = Picture.Rgb mood 100 100;
  Picture.picture (300, 300) [Picture.Circle (100, 100) 60 color]
};

let main: Picture.mainType = Interaction.simulate {mood: 120} showPerson updatePerson;
