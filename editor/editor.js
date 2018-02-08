
var editor = ace.edit("editor");
var StatusBar = ace.require("ace/ext/statusbar").StatusBar;
StatusBar = new StatusBar(editor, document.getElementById("statusBar"));
ace.require('ace/ext/settings_menu').init(editor);
editor.setTheme("ace/theme/xcode");
editor.session.setMode("ace/mode/c_cpp");
editor.setAutoScrollEditorIntoView(true);
editor.setOption("maxLines", 1000);
editor.setOption("minLines", 25);
editor.commands.addCommands([{
	name: "showSettingsMenu",
	bindKey: {win: "Ctrl-q", mac: "Ctrl-q"},
	exec: function(editor) {
		editor.showSettingsMenu();
	},
	readOnly: true
}]);
axios.get("example.bas")
	.then(function(response){
		editor.setValue(response.data);
		editor.focus();
	})
	.catch(function(error){
		editor.focus();
	});
function submitscrtip()
{
	alert("sure to submit!");
}
