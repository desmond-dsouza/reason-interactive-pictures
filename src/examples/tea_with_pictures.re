open Tea.App;

open Tea.Html;

module I = Interaction;

module P = Picture;

type msg =
  | Inc
  | Dec
  | Set int
  | Tick float;

let tick t => Tick t;

type model = Simulate.person;

let initialModel = Simulate.initialPerson;

let update (model: model) (msg: msg) :model => {
  Js.log (model, msg);
  switch msg {
  | Inc => {...model, base_mood: model.base_mood + 40}
  | Dec => {...model, base_mood: model.base_mood - 40}
  | Set i => {...model, base_mood: i}
  | Tick t => Simulate.updatePerson t model
  }
};

let view model =>
  div
    []
    [
      div [] [text {j| Model: $model |j}],
      Simulate.showPerson model,
      button [onClick Inc] [text "+"],
      button [onClick Dec] [text "-"]
    ];

/*let main = beginnerProgram {model: initialModel, update, view};*/
let main: Picture.display msg = Interaction.interact initialModel view update (20., tick);
