(window.webpackJsonp=window.webpackJsonp||[]).push([[0],{18:function(e,t,n){e.exports=n.p+"static/media/rick.fcf97f8c.png"},24:function(e,t,n){e.exports=n(39)},29:function(e,t,n){},30:function(e,t,n){},39:function(e,t,n){"use strict";n.r(t);var a=n(0),o=n.n(a),r=n(14),i=n.n(r),c=n(19),s=n(5),l=(n(29),n(15)),d=n(16),u=n(22),p=n(17),h=n(7),g=n(23),m=n(18),v=n.n(m),f=(n(30),function(e){function t(){var e;return Object(l.a)(this,t),(e=Object(u.a)(this,Object(p.a)(t).call(this))).handleKeyPress=function(t){" "===t.key&&(e.toggleRecording(),document.removeEventListener("keydown",e.handleKeyPress,!0))},e.state={input:"",start:1,recognition:""},e.handleKeyPress=e.handleKeyPress.bind(Object(h.a)(e)),e.toggleRecording=e.toggleRecording.bind(Object(h.a)(e)),e.recorder=null,e}return Object(g.a)(t,e),Object(d.a)(t,[{key:"componentDidMount",value:function(){document.addEventListener("keydown",this.handleKeyPress)}},{key:"toggleRecording",value:function(){var e=this;if(1===this.state.start){console.log("we start recording",this.state.start),this.setState({start:0,recognition:""});navigator.mediaDevices.getUserMedia({audio:{sampleRate:16e3,channelCount:1}}).then(function(t){console.log(e),e.recorder=new MediaRecorder(t),e.recorder.start();var n=[];e.recorder.addEventListener("dataavailable",function(e){n.push(e.data)}),e.recorder.addEventListener("stop",function(){var t=new Blob(n,{type:"audio/wav"}),a=URL.createObjectURL(t);fetch("http://127.0.0.1:6060/api/sendaudio",{method:"post",headers:{"Content-Type":"audio/wav"},body:t}).then(function(e){return e.text()}).then(function(t){console.log(t),e.setState({recognition:t})});new Audio(a)})})}else console.log("we stop recording",this.state.start),this.setState({start:1}),this.recorder.stop()}},{key:"render",value:function(){return o.a.createElement("div",{className:"App"},o.a.createElement("header",{className:"App-header"},o.a.createElement("img",{src:v.a,className:"App-logo",alt:"logo"}),1===this.state.start?o.a.createElement("h2",null," Speak with Rick"):o.a.createElement("h2",null," Speaking ..."),1===this.state.start?o.a.createElement("button",{id:"speak",type:"button",disabled:!0}," Hit 'Space' and start speaking "):o.a.createElement("button",{type:"button",id:"stop"},"Hit 'Space' and wait for Rick answer "),o.a.createElement("p",null," ",o.a.createElement("i",null,'Try: "Hello", "Open Slack", "Look for 42 on Google" ... ')),""===this.state.recognition?o.a.createElement("p",null):o.a.createElement("p",{id:"recognition"}," ",this.state.recognition," ")))}}]),t}(o.a.Component));Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));var w=o.a.createElement(c.a,null,o.a.createElement("div",null,o.a.createElement(s.a,{exact:!0,path:"/",component:f})));i.a.render(w,document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then(function(e){e.unregister()})}},[[24,1,2]]]);
//# sourceMappingURL=main.1db44df1.chunk.js.map