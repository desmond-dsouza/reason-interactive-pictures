type point = (int, int);

type color = string;

type figure =
  | Circle point int color
  | Rect point int int color;

let render f => {
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  let str = string_of_int;
  switch f {
  | Circle (x_, y_) r_ c_ =>
    S.circle [SA.cx (str x_), SA.cy (str y_), SA.r (str r_), SA.fill c_] []
  | Rect (x_, y_) w_ h_ c_ =>
    S.rect [SA.x (str x_), SA.y (str y_), SA.width (str w_), SA.height (str h_), SA.fill c_] []
  }
};
