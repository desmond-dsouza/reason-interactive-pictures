type person = {mood: int};

let updatePerson t {mood} => {
  let delta = 70. *. sin (t /. 150.);
  let mood' = mood + int_of_float delta;
  {mood: mood'}
};

let showPerson {mood} => {
  let color = Picture.Rgb mood 100 100;
  Picture.picture (300, 300) [Picture.Circle (100, 100) 60 color]
};

let main: Picture.mainType = Interaction.simulate {mood: 100} showPerson updatePerson;
