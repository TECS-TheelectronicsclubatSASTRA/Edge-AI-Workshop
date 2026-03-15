function doPost(e) {

  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var data = JSON.parse(e.postData.contents);

  var label = data.label;
  var samples = data.data;

  for (var i = 0; i < samples.length; i++) {
    sheet.appendRow([
      new Date(),
      samples[i][0],
      samples[i][1],
      samples[i][2],
      samples[i][3],
      samples[i][4],
      samples[i][5],
      label
    ]);
  }

  return ContentService.createTextOutput("Batch Received");
}
