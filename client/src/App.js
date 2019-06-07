import React from 'react';
import logo from './rick.png';
import pickle from './pickle.png'
import Recorder from 'recorder-js';
import { ReactMic } from 'react-mic';
import './App.css';


class App extends React.Component {

    constructor() {
        super();
        this.state = {
            input: "",
            recognition: "",
            record: false,
            pickle_mode: false
        }
        this.handleKeyPress = this.handleKeyPress.bind(this);
        this.toggleRecording = this.toggleRecording.bind(this);
        this.recorder = null;
    }

    handleKeyPress = (event) => {
        if (event.key === ' ') {
            this.toggleRecording();
            document.removeEventListener('keydown', this.handleKeyPress, true);
        }
    }

    componentDidMount() {
        const isFirefox = typeof InstallTrigger !== 'undefined';
        const isChrome = !!window.chrome && (!!window.chrome.webstore || !!window.chrome.runtime);
        if (isFirefox || isChrome) {
            document.addEventListener('keydown', this.handleKeyPress);
        }
        else {
            alert("Nobody exists on purpose. Nobody belongs anywhere. We’re all going to die. Come watch TV.\n\nBy the way, this browser is not supported because it does not handle mediarecorder. Please, use CHROME or FIREFOX !")
        }
    }


    toggleRecording() {
        if (this.state.record === false) {
            this.setState({ record: true, recognition: "" })

            const audioContext = new window.AudioContext() || new window.webkitAudioContext()

            this.recorder = new Recorder(audioContext)

            const constraints = {
                audio: {
                    sampleRate: 16000,
                    channelCount: 1
                }
            }
            navigator.mediaDevices.getUserMedia(constraints)
                .then(stream => this.recorder.init(stream))
                .catch(err => console.log('There is a bug streaming...', err))
                .then(() => {
                    this.recorder.start()
                })
        }
        else {
            this.setState({record: false});
            this.recorder.stop()
                .then(({ blob, buffer }) => {
                    // buffer is an AudioBuffer

                    //to replay the audio
                    const audioUrl = URL.createObjectURL(blob);
                    console.log(audioUrl)
                    //const audio = new Audio(audioUrl);
                    //audio.play();

                    //send to the server
                    const formData = new FormData();
                    formData.append('audio', blob);
                    fetch('http://127.0.0.1:6060/api/sendaudio', {
                        method: "post",
                        headers: { 'Content-Type': 'audio/wav' },
                        body: formData
                    })
                        .then(response => {
                            return response.text()
                        }).then(text => {
                            console.log(text);
                            if (text.toLowerCase() === "pickle")
                                this.setState({pickle_mode: true})
                            this.setState({ recognition: text })
                        });
                });
        }
    }

    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <img src={this.state.pickle_mode === false ? logo : pickle} className="App-logo" alt="logo" />
                    {this.state.record === false ? <h2> Speak with Rick</h2> : <h2> Speaking ...</h2>}
                    {this.state.record === false ? <button id="speak" type="button" disabled> Hit 'Space' and start speaking </button> : <button type="button" id="stop">Hit 'Space' and wait for the answer </button>}
                    {this.state.recognition === "" ? <p id="comment"> Try: "Hello", "Open Slack", "Look for 42 on Google" ...</p> : <p id="recognition"> ' {this.state.recognition} ' </p>}
                    <ReactMic record={this.state.record} className="sound-wave" onStop={this.onStop} onData={this.onData} strokeColor="#00FF00" backgroundColor="#282C34" />
                </header>
            </div>
        );
    }
}

export default App;
