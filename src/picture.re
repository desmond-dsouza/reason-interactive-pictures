type point = (int, int);

type color =
  | Red
  | Yellow
  | Green
  | Orange
  | Pink
  | Grey
  | Brown
  | Purple
  | Blue
  | Rgb int int int;

let string_of_color c =>
  switch c {
  | Red => "red"
  | Yellow => "yellow"
  | Green => "green"
  | Orange => "orange"
  | Pink => "pink"
  | Grey => "grey"
  | Brown => "brown"
  | Purple => "purple"
  | Blue => "blue"
  | Rgb r g b => "rgb(" ^ string_of_int r ^ "," ^ string_of_int g ^ "," ^ string_of_int b ^ ")"
  };

type figure =
  | Circle point int color
  | Rect point int int color;

let render f => {
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  let str = string_of_int;
  let col = string_of_color;
  switch f {
  | Circle (x_, y_) r_ c_ =>
    S.circle [SA.cx (str x_), SA.cy (str y_), SA.r (str r_), SA.fill (col c_)] []
  | Rect (x_, y_) w_ h_ c_ =>
    S.rect
      [SA.x (str x_), SA.y (str y_), SA.width (str w_), SA.height (str h_), SA.fill (col c_)] []
  }
};

type mainType = Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg;

let picture (width, height) figures => {
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  let w = (width |> string_of_int) ^ "px";
  let h = (height |> string_of_int) ^ "px";
  let nodes = figures |> List.map render;
  S.svg [SA.width w, SA.height h] nodes
};
