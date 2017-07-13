type person = {
  base_mood: int,
  mood_swing: int,
  shift: int
};

let initialPerson = {base_mood: 120, mood_swing: 0, shift: 0};

let showPerson {base_mood, mood_swing, shift} => {
  let mood = base_mood + mood_swing;
  let color = Picture.Rgb mood 100 100;
  let r = max (10 + mood) 10;
  let (headX, headY) = (250 + shift, 260);
  let head = Picture.Circle (headX, headY) r color;
  let (bodyLen, bodyThick) = (30, 5);
  let (bodyTop, bodyBot) = ((headX, headY + r), (headX, headY + r + bodyLen));
  let body = Picture.Line bodyTop bodyBot bodyThick Black;
  let arms =
    Picture.Line (headX - 15, headY + r + 15) (headX + 15, headY + r + 15) bodyThick Black;
  let legL = Picture.line bodyBot bodyLen 120 bodyThick Black;
  let legR = Picture.line bodyBot bodyLen 60 bodyThick Black;
  /*Js.log {j|Head: $head Body: $body|j};*/
  Picture.picture (1000, 600) [head, body, arms, legL, legR]
};

let main: Picture.simpleDisplay = Interaction.draw (showPerson initialPerson);
