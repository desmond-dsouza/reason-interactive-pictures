/* TODO: pictureOf, animationOf, etc. naming, see https://code.world/ */
/* TODO: easy speed-control UI */
/* TODO: real-time graphs (JS interop: https://goo.gl/DlcmvT) */
module Cmd = Tea.Cmd;

module Time = Tea.Time;

type time = Time.t;

type never = Tea_task.never;

type mouse = {x: float, y: float};

type keyCode = int;

type size = {width: int, height: int};

type key =
  | Tab
  | Enter
  | Shift
  | Space
  | Left
  | Up
  | Right
  | Down
  | Zero
  | One
  | Two
  | Three
  | Four
  | Five
  | Six
  | Seven
  | Eight
  | Nine
  | A
  | B
  | C
  | D
  | E
  | F
  | G
  | H
  | I
  | J
  | K
  | L
  | M
  | N
  | O
  | P
  | Q
  | R
  | S
  | T
  | U
  | V
  | W
  | X
  | Y
  | Z
  | Other keyCode;

type window = {top: float, bottom: float, left: float, right: float};

let window t b l r => {
  top: float_of_int t,
  bottom: float_of_int b,
  left: float_of_int l,
  right: float_of_int r
};

type msg =
  | TimeTick time
  | MouseClick mouse
  | MouseDown mouse
  | MouseUp mouse
  | MouseMove mouse
  | KeyDown key
  | KeyUp key
  | WindowResize window;

let timeTick t => TimeTick t;

let windowResize w => WindowResize w;

let (>>) f g x => x |> f |> g;

type model 'm = {window, time, model: 'm};

type drawing =
  | Program never (model unit) msg;

type animation =
  | Program never (model unit) msg;

type simulation 'model =
  | Program never (model 'model) msg;

type interaction 'model =
  | Program never (model 'model) msg;

let init (model: 'm) (_flag: 'flags) :(model 'm, Cmd.t msg) => {
  let windowCmd: Cmd.t msg = Cmd.none;
  /* Tea_task.perform (sizeToWindow >> windowResize) window.size; */
  ({window: window 0 0 0 0, time: 0., model}, Cmd.batch [windowCmd]) /* [windowCmd] */
};

let windowResizeSub = Tea.Sub.none; /* Web.Window.resizes (sizeToWindow >> windowResize); */

let drawUpdate model msg =>
  switch msg {
  | WindowResize newWindow => ({...model, window: newWindow}, Cmd.none)
  | _ => (model, Cmd.none)
  };

let windowToSize {top, bottom, left, right} => {
  let width = int_of_float (right -. left);
  let height = int_of_float (top -. bottom);
  {width, height}
};

let accumTimeSub (time: time) :Tea_sub.t msg =>
  /*Tea.AnimationFrame.diffs (fun key::_ diff => diff +. time |> timeTick);*/
  Time.every 60.0 timeTick;

/*viewModelWindowToHtml : (model -> Collage.Form) -> model -> window -> Html.Html msg*/
let viewModelWindowToHtml view model window => {
  let {width, height} = windowToSize window;
  /*Collage.collage width height [view model] |> Element.toHtml*/
  view model
};

/* ******** Draw:: view : Html ********* */
let draw view =>
  Tea.App.standardProgram {
    init: init (),
    view: fun {window} => viewModelWindowToHtml (fun _ => view) () window,
    update: drawUpdate,
    subscriptions: fun _ => windowResizeSub
  };

/* ******** Animate:: view : time -> Html ********* */
let animateSubs {time} => Tea.Sub.batch [accumTimeSub time, windowResizeSub];

let animateUpdate model msg =>
  switch msg {
  | TimeTick newTime => ({...model, time: newTime}, Cmd.none)
  | WindowResize newWindow => ({...model, window: newWindow}, Cmd.none)
  | _ => (model, Cmd.none)
  };

let animate view =>
  Tea.App.standardProgram {
    init: init (),
    view: fun {time, window} => viewModelWindowToHtml view time window,
    update: animateUpdate,
    subscriptions: animateSubs
  };

/* ******** Simulate: view : model -> time -> Html ********* */
let simulateUpdate update ({model} as simulateModel) msg =>
  switch msg {
  | TimeTick newTime =>
    let updatedModel = update newTime model;
    let newModel =
      /*-- necessary for lazy*/
      if (updatedModel == model) {
        model
      } else {
        updatedModel
      };
    ({...simulateModel, time: newTime, model: newModel}, Cmd.none)
  | WindowResize newWindow => ({...simulateModel, window: newWindow}, Cmd.none)
  | _ => (simulateModel, Cmd.none)
  };

let simulateSubs {time} => Tea.Sub.batch [accumTimeSub time, windowResizeSub];

let simulate (start: 'm) view (update: time => 'm => 'm) =>
  Tea.App.standardProgram {
    init: init start,
    view: fun {model, window} => /* lazy3 */ viewModelWindowToHtml view model window,
    update: simulateUpdate update,
    subscriptions: simulateSubs
  };
/* ******** Interact & beyond: directly use beginnerProgram & standardProgram ********* */
