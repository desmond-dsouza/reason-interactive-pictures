type point = (int, int);

type color =
  | Red
  | Yellow
  | Green
  | Orange
  | Pink
  | Brown
  | Purple
  | Blue
  | Black
  | White
  | Grey
  | Named string
  | Rgb int int int;

let string_of_color c =>
  switch c {
  | Red => "red"
  | Yellow => "yellow"
  | Green => "green"
  | Orange => "orange"
  | Pink => "pink"
  | Brown => "brown"
  | Purple => "purple"
  | Blue => "blue"
  | Black => "black"
  | White => "white"
  | Grey => "grey"
  | Named s => s
  | Rgb r g b => {j|rgb($r,$g,$b)|j}
  };

type url = string;

/* TODO: minimal constructors: Line Ellipse Polygon Text Image Group */
/* ... but then more difficult to do things like generic Labeled? */
type figure =
  | Circle point int color
  | Rect point int int color
  | Line point point int color
  | Arrow point point int color
  | Polygon (list point) color
  | Polyline (list point) color
  | Image point int int url
  | Text point string
  | Labeled string figure;

let labelPos (f: figure) =>
  switch f {
  | Circle pos _ _
  | Rect pos _ _ _
  | Line _ pos _ _
  | Arrow _ pos _ _
  | Polygon [pos, ..._] _
  | Polyline [pos, ..._] _
  | Image pos _ _ _ => pos
  | _ => raise (Invalid_argument "no labelPos defined")
  };

let line (x: int, y: int) (l: int) (theta: int) (thick: int) (color: color) => {
  let radians = float_of_int theta *. 2.0 *. 3.14159 /. 360.;
  let fl = float_of_int;
  let x2 = fl x +. fl l *. cos radians |> int_of_float;
  let y2 = fl y +. fl l *. sin radians |> int_of_float;
  Line (x, y) (x2, y2) thick color
};

module S = Tea.Svg;

module SA = Tea.Svg.Attributes;

let arrowHead (x1, y1) (x2, y2) lineWidth color => {
  let i = int_of_float;
  let f = float_of_int;
  let (vX, vY) = (x2 - x1 |> f, y2 - y1 |> f);
  let len = vX *. vX +. vY *. vY |> sqrt;
  let (uX, uY) = (vX /. len, vY /. len);
  let headL = 3. +. f lineWidth *. 2.;
  let (dX, dY) = (-. (headL *. uX), -. (headL *. uY));
  let (idX, idY) = (i dX, i dY);
  let (bX, bY) = (x2 + idX, y2 + idY);
  let (c1X, c1Y) = (bX - idY, bY + idX);
  let (c2X, c2Y) = (bX + idY, bY - idX);
  [Line (x2, y2) (c1X, c1Y) lineWidth color, Line (x2, y2) (c2X, c2Y) lineWidth color]
};

let stylesheet url =>
  Tea.Html.node
    "link" [Vdom.prop "rel" "stylesheet", Tea.Html.type' "text/css", Tea.Html.href url] [];

let cssBulmaUrl = "https://cdnjs.cloudflare.com/ajax/libs/bulma/0.4.2/css/bulma.min.css";

let cssPureCssUrl = "https://unpkg.com/purecss@1.0.0/build/pure-min.css";

let cssFontAwesomeUrl = "https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css";

let cssTachyonsUrl = "https://unpkg.com/tachyons@4.7.0/css/tachyons.min.css";

let rec render (f: figure) => {
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
  | Arrow p1 p2 w c =>
    let (x1, y1) = p1;
    let (x2, y2) = p2;
    let head = List.map render (arrowHead p1 p2 w c);
    let line =
      S.line
        [
          SA.x1 (str x1),
          SA.y1 (str y1),
          SA.x2 (str x2),
          SA.y2 (str y2),
          SA.stroke (col c),
          SA.strokeWidth (str w)
        ]
        [];
    S.g [] [line, ...head]
  | Polygon points color =>
    let pts = List.fold_left (fun s (x, y) => s ^ str x ^ "," ^ str y ^ " ") "" points;
    S.polygon [SA.points pts, SA.fill (string_of_color color)] []
  | Polyline points color =>
    let pts = List.fold_left (fun s (x, y) => s ^ str x ^ "," ^ str y ^ " ") "" points;
    S.polyline [SA.points pts, SA.stroke (string_of_color color), SA.fill "none"] []
  | Image (x0, y0) w h url =>
    S.svgimage
      [SA.x (str x0), SA.y (str y0), SA.width (str w), SA.height (str h), SA.xlinkHref url] []
  | Text (x0, y0) s => S.text' [SA.x (str x0), SA.y (str y0)] [S.text s]
  | Labeled label fig => S.g [] [Text (labelPos fig) label |> render, fig |> render]
  }
};

type simpleDisplay =
  Js.null_undefined Web.Node.t => unit => Tea.App.programInterface Interaction.msg;

type interactiveDisplay 'msg =
  Js.null_undefined Web.Node.t => unit => Tea.App.programInterface 'msg;

let picture (width: int, height: int) figures => {
  module S = Tea.Svg;
  module SA = Tea.Svg.Attributes;
  let w = {j|$(width)px|j};
  let h = {j|$(height)px|j};
  let nodes = figures |> List.map render;
  S.svg [SA.width w, SA.height h] nodes
};
