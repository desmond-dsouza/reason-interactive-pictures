open Tea.Svg;

open Tea.Svg.Attributes;

let myView t => {
  let dx = 70. *. sin (t /. 150.);
  let x = 100 + int_of_float dx;
  let dy = 70. *. sin (t /. 150. -. 2.);
  let y = 100 + int_of_float dy;
  let color = "rgb(" ^ string_of_int y ^ ",100,100)";
  Js.log color;
  let c = circle [cx (x |> string_of_int), cy (y |> string_of_int), r "20", fill color] [];
  svg [width "300px", height "300px"] [c]
};

let main: Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg =
  Interaction.animate myView;
