let model = 0;

let update (m: int) (msg: string) :int => m;

let view _ :Vdom.t string => Tea.Html.(div [] [text "Howdy Doo! (from app.re)"]);

let main = Tea.App.beginnerProgram {model, view, update};
