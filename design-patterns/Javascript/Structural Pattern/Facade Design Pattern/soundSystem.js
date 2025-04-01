// Class for sound system functionality

class SoundSystem {
    on() {
    console.log("Sound system is on");
  }

  setVolume(volume) {
    console.log(`Setting volume to ${volume}`);
  }

  off() {
    console.log("Sound system is off");
  }
}

module.exports = SoundSystem;
