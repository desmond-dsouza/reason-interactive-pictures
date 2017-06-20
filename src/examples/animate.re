module P = Picture;

let myView t => {
  let dx = 70. *. sin (t /. 150.);
  let x = 100 + int_of_float dx;
  let dy = 70. *. sin (t /. 150. -. 2.);
  let y = 100 + int_of_float dy;
  let color = P.Rgb y 100 100;
  P.picture (300, 300) [P.Circle (x, y) 20 color]
};

let main: Picture.display Interaction.msg = Interaction.animate myView delta_ms::10.0;
