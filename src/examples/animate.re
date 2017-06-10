let myView t => {
  open Picture;
  let dx = 70. *. sin (t /. 150.);
  let x = 100 + int_of_float dx;
  let dy = 70. *. sin (t /. 150. -. 2.);
  let y = 100 + int_of_float dy;
  let color = Rgb y 100 100;
  picture (300, 300) [Circle (x, y) 20 color]
};

let main: Picture.mainType = Interaction.animate myView delta_ms::10.0;
