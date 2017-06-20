module Cmd = Tea.Cmd;

module Time = Tea.Time;

type time = Time.t;

type never = Tea_task.never;

type msg =
  | TimeTick time;

let timeTick t => TimeTick t;

type model 'm = {
  time,
  model: 'm
};

let init (model: 'm) (_flag: 'flags) :(model 'm, Cmd.t msg) => (
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
    (initialModel: 'm)
    (view: 'm => Vdom.t 'msg)
    (update: 'm => 'msg => 'm)
    (delta_ms: time, tick: time => 'msg) =>
  Tea.App.standardProgram {
    init: fun _flags => (initialModel, Tea.Cmd.none),
    update: fun m msg => (update m msg, Tea.Cmd.none),
    view,
    subscriptions: fun _m => Tea.Time.every delta_ms tick
  };
