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
  | Black
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
  | Black => "black"
  | Rgb r g b => {j|rgb($r,$g,$b)|j}
  };

type figure =
  | Circle point int color
  | Rect point int int color
  | Line point point int color;

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
  | Line (x1_, y1_) (x2_, y2_) w_ c_ =>
    S.line
      [
        SA.x1 (str x1_),
        SA.y1 (str y1_),
        SA.x2 (str x2_),
        SA.y2 (str y2_),
        SA.stroke (col c_),
        SA.strokeWidth (str w_)
      ]
      []
  }
};

type mainType = Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg;

let picture (width, height) figures => {
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  let w = {j|$(width)px|j};
  let h = {j|$(height)px|j};
  let nodes = figures |> List.map render;
  S.svg [SA.width w, SA.height h] nodes
};
