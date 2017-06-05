open Tea.Svg;

open Tea.Svg.Attributes;

type person = {mood: int};

let updatePerson t {mood} => {
  Js.log t;
  let delta = 70. *. sin (t /. 150.);
  let mood' = mood + int_of_float delta;
  {mood: mood'}
};

let showPerson {mood} => {
  let color = "rgb(" ^ string_of_int mood ^ ",100,100)";
  let c = circle [cx "100", cy "100", r "60", fill color] [];
  svg [width "300px", height "300px"] [c]
};

let main: Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg =
  Interaction.simulate {mood: 100} showPerson updatePerson;
