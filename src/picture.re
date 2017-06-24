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

type url = string;

type figure =
  | Circle point int color
  | Rect point int int color
  | Line point point int color
  | Arrow point point int color
  | Polygon (list point) color
  | Polyline (list point) color
  | Image point int int url;

module S = Tea.Svg;

module SA = Tea.Svg.Attributes;

let arrowMarker () :Vdom.t 'm =>
  S.marker
    [
      SA.id "arrow",
      SA.markerWidth "10",
      SA.markerHeight "10",
      SA.refX "0",
      SA.refY "3",
      SA.orient "auto",
      SA.fill "black"
    ]
    [S.path [SA.d "M0,0 L0, 6,L9, 3 z", SA.fill "#f00"] []];

let render f => {
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
  | Arrow (x1_, y1_) (x2_, y2_) w_ c_ =>
    S.line
      [
        SA.x1 (str x1_),
        SA.y1 (str y1_),
        SA.x2 (str x2_),
        SA.y2 (str y2_),
        SA.stroke (col c_),
        SA.strokeWidth (str w_),
        SA.markerEnd "url(#arrow)"
      ]
      []
  | Polygon points color =>
    let pts = List.fold_left (fun s (x, y) => s ^ str x ^ "," ^ str y ^ " ") "" points;
    S.polygon [SA.points pts, SA.fill (string_of_color color)] []
  | Polyline points color =>
    let pts = List.fold_left (fun s (x, y) => s ^ str x ^ "," ^ str y ^ " ") "" points;
    S.polyline [SA.points pts, SA.stroke (string_of_color color), SA.fill "none"] []
  | Image (x0, y0) w h url =>
    S.svgimage
      [SA.x (str x0), SA.y (str y0), SA.width (str w), SA.height (str h), SA.xlinkHref url] []
  }
};

type simpleDisplay =
  Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg;

type interactiveDisplay 'msg =
  Js.null_undefined Web.Node.t => unit => Tea.App.programInterface 'msg;

let picture (width, height) figures => {
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  let w = {j|$(width)px|j};
  let h = {j|$(height)px|j};
  let nodes = figures |> List.map render;
  let defs = [S.defs [] [arrowMarker ()]];
  let children = List.append defs nodes;
  S.svg [SA.width w, SA.height h] children
};
