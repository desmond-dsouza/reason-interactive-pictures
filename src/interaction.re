/* TODO: pictureOf, animationOf, etc. naming, see https://code.world/ */
/* TODO: easy speed-control UI */
/* TODO: real-time graphs (JS interop: https://goo.gl/DlcmvT) */
module Cmd = Tea.Cmd;

module Time = Tea.Time;

type time = Time.t;

type never = Tea_task.never;

type msg =
  | TimeTick time;

let timeTick t => TimeTick t;

type model 'm = {time, model: 'm};

let init (model: 'm) (_flag: 'flags) :(model 'm, Cmd.t msg) => (
  {time: 0., model},
  Cmd.batch [Cmd.none]
);

let drawUpdate model msg =>
  switch msg {
  | TimeTick _ => (model, Cmd.none)
  };

let accumTimeSub (time: time) :Tea_sub.t msg => Time.every 60.0 timeTick;

let viewModelWindowToHtml view model window => view model;

/* ******** Draw:: view : Html ********* */
let draw view =>
  Tea.App.standardProgram {
    init: init (),
    view: fun _ => view,
    update: drawUpdate,
    subscriptions: fun _ => Tea.Sub.none
  };

/* ******** Animate:: view : time -> Html ********* */
let animateSubs {time} => Tea.Sub.batch [accumTimeSub time, Tea.Sub.none];

let animateUpdate model msg =>
  switch msg {
  | TimeTick newTime => ({...model, time: newTime}, Cmd.none)
  };

let animate view =>
  Tea.App.standardProgram {
    init: init (),
    view: fun {time} => view time,
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
  };

let simulateSubs {time} => Tea.Sub.batch [accumTimeSub time, Tea.Sub.none];

let simulate (start: 'm) view (update: time => 'm => 'm) =>
  Tea.App.standardProgram {
    init: init start,
    view: fun {model} => /* lazy3 */ view model,
    update: simulateUpdate update,
    subscriptions: simulateSubs
  };
