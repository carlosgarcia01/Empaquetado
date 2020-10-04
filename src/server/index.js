const app = require("./server");
const addon = require("../../build/Release/addon");
const obj = new addon.usbdevWrap(0);

obj.MainWrap();

setInterval(() => {
  obj.processEvents();
}, 300);

app.use("/objOn", (req, res) => {
  res.json({ res: obj.serviceSlotWrap() });
});

app.use("/objOff", (req, res) => {
  res.json({ res: obj.serviceSlotWrapOff() });
});

app.use("/objAdd", (req, res) => {
  res.json({ res: obj.plusOneWrap() });
});

app.listen(app.get("port"), () => {
  console.log(`server on localhost:${app.get("port")}`);
});
