class Observer {
  update(temperature) {
    throw new Error("Method 'update()' must be implemented");
  }
}

class WebUI extends Observer {
  update(temperature) {
    console.log(`Temperature showing in web UI: ${temperature}`);
  }
}

class MobileUI extends Observer {
  update(temperature) {
    console.log(`Temperature showing in mobile UI: ${temperature}`);
  }
}

module.exports = {
  WebUI,
  MobileUI,
};
