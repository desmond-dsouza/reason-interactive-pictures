module Cmd = Tea.Cmd;

module Time = Tea.Time;

type time = Time.t;

type never = Tea_task.never;

type msg =
  | TimeTick time;

let debug (s: string) (a: 'a) => {
  Js.log (s, a);
  a
};

let timeTick t => TimeTick t;

type timedModel 'm = {
  time,
  model: 'm
};

let init (model: 'm) (_flag: 'flags) :(timedModel 'm, Cmd.t msg) => (
  {time: 0., model},
  Cmd.batch [Cmd.none]
);

let drawUpdate model msg =>
  switch msg {
  | TimeTick _t => (model, Cmd.none)
  };

let timerSubscription (delta_ms: time) _ => Time.every delta_ms timeTick;

/* ******** Draw:: view : Html ********* */
let draw view =>
  Tea.App.standardProgram {
    init: init (),
    view: fun _ => view,
    update: drawUpdate,
    subscriptions: fun _ => Tea.Sub.none
  };

/* ******** Animate:: view : time -> Html ********* */
let animateUpdate model msg =>
  switch msg {
  | TimeTick newTime => ({...model, time: newTime}, Cmd.none)
  };

let animate view ::delta_ms=60.0 =>
  Tea.App.standardProgram {
    init: init (),
    view: fun {time} => view time,
    update: animateUpdate,
    subscriptions: timerSubscription delta_ms
  };

/* ******** Simulate: view : model -> time -> Html ********* */
let simulateUpdate update {model} msg =>
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
    ({time: newTime, model: newModel}, Cmd.none)
  };

let simulate (start: 'm) view (update: time => 'm => 'm) ::delta_ms =>
  Tea.App.standardProgram {
    init: init start,
    view: fun {time, model} => view model,
    update: simulateUpdate update,
    subscriptions: timerSubscription delta_ms
  };

/* ******** Interact: initialModel view update ::delta_ms ********* */
let interact
    (initialModel: 'model)
    (view: 'model => Vdom.t 'msg)
    (update: 'model => 'msg => 'model)
    ::every=? =>
  /* (delta_ms: time, tick: time => 'msg) => */
  Tea.App.standardProgram {
    init: fun _flags => (initialModel, Tea.Cmd.none),
    update: fun m msg => (update m msg, Tea.Cmd.none),
    view,
    subscriptions:
      switch every {
      | None => (fun _m => Tea.Sub.none)
      | Some (deltaT, tickMsg) => (fun _m => Tea.Time.every deltaT tickMsg)
      }
  };

/* ***** Convenient Widgets ****** */
/* TODO: make extension of Html module */
module H = Tea.Html;

module A = Tea.Html.Attributes;

let labeledWidget label' widget => H.div [] [H.text label', H.text " ", widget];

let slider ::label' ::min ::max ::init action::(action: int => 'msg) => {
  let sliderMsg str => action (int_of_string str);
  let widget =
    H.input'
      [
        H.type' "range",
        A.min (string_of_int min),
        A.max (string_of_int max),
        H.value (string_of_int init),
        H.onInput sliderMsg
      ]
      [];
  labeledWidget label' widget
};

let selector ::label' ::choices ::init action::(action: 'a => 'msg) => {
  let stringify x => {j|$x|j};
  let options =
    List.map
      (fun a => H.option' (a == init ? [A.selected true] : [H.noProp]) [a |> stringify |> H.text])
      choices;
  let chosen str => List.find (fun x => stringify x == str) choices;
  let msg str => action (chosen str);
  let sel = H.select [H.onChange msg] options;
  labeledWidget label' sel
};
