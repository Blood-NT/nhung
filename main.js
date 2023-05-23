var checkboxes = document.querySelectorAll('input[type=checkbox]');
var den1 = "TAT";
var den2 = "TAT";
var den3 = "TAT";
var den4 = "TAT";
var quat = "TAT";
var nhietdo = 121;
var doam = 121;


const temperatureElement = document.getElementById('temperature');
const humidityElement = document.getElementById('humidity');


var dataThietBi = {
  DEN1: den1,
  DEN2: den2,
  DEN3: den3,
  DEN4: den4,
  QUAT: quat,
};
checkboxes.forEach((checkbox, index) => {
  checkbox.dataset.index = index;
  checkbox.addEventListener('change', () => {
    const isChecked = checkbox.checked;
    const lightName = checkbox.parentNode.parentNode.querySelector('p').textContent;
    const checkboxIndex = checkbox.dataset.index;
    if (!isChecked) {
      if (checkboxIndex === "0") {
        den1 = "TAT";
      } else if (checkboxIndex === "1") {
        den2 = "TAT";
      } else if (checkboxIndex === "2") {
        den3 = "TAT";
      } else if (checkboxIndex === "3") {
        den4 = "TAT";
      }
      else if (checkboxIndex === "4") {
        quat = "TAT";
      }
      alert(lightName + " is turned off");
    } else {
      if (checkboxIndex === "0") {
        den1 = "BAT";
      } else if (checkboxIndex === "1") {
        den2 = "BAT";
      } else if (checkboxIndex === "2") {
        den3 = "BAT";
      } else if (checkboxIndex === "3") {
        den4 = "BAT";
      }
      else if (checkboxIndex === "4") {
        quat = "BAT";
      }
      alert(lightName + " is turned on");
    }
    updateData()
    sendData(dataThietBi);
  });
});
function updateData() {

   dataThietBi = {
    DEN1: den1,
    DEN2: den2,
    DEN3: den3,
    DEN4: den4,
    QUAT: quat,

  };
}

////

import { initializeApp } from "https://www.gstatic.com/firebasejs/9.22.0/firebase-app.js";
import { getDatabase, ref, onValue, set } from "https://www.gstatic.com/firebasejs/9.22.0/firebase-database.js";

import { getAnalytics } from "https://www.gstatic.com/firebasejs/9.22.0/firebase-analytics.js";

const firebaseConfig = {
    // apiKey: "AIzaSyARZZfWifBSXQCPbAWj-yD4fhIc0AhBLyo",
    apiKey: "dIY4zoWvWa2GbvBLfPz7DITzHRO6zQlyPJQtahhu",
    authDomain: "snolan-iot.firebaseapp.com",
    databaseURL: "https://snolan-iot-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "snolan-iot",
    storageBucket: "snolan-iot.appspot.com",
    messagingSenderId: "1061665752997",
    appId: "1:1061665752997:web:83edb7d8c001c782d80a4c",
    measurementId: "G-3XWGZJFCM9"
};
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const database = getDatabase(app);       
function listenToData() {
    const checkStatus = ref(database, "STATUS");
    const checkThietBi = ref(database, "THIETBI");
    onValue(checkStatus, (snapshot) => {
        const data = snapshot.val();
        doam = data.DOAM
        nhietdo = data.NHIETDO
        console.log("Dữ liệu từ Firebase Realtime Database:", doam, nhietdo);
        updateTandH(data.NHIETDO,data.DOAM)
    }, (error) => {
        console.error("Lỗi khi lắng nghe dữ liệu:", error);
    });
    onValue(checkThietBi, (snapshot) => {
        const data = snapshot.val();
        den1 = data.DEN1
        den2 = data.DEN2
        den3 = data.DEN3
        den4 = data.DEN4
        quat = data.QUAT
        checkbtn( den1,den2,den3,den4,quat);
        console.log("Dữ liệu từ Firebase Realtime Database:", den1, den2, den3, den4, quat);
    }, (error) => {
        console.error("Lỗi khi lắng nghe dữ liệu:", error);
    });
}
function sendData( THIETBI) {
    updateData() 
    const checkThietBi = ref(database, "THIETBI");
    set(checkThietBi, THIETBI)
        .then(() => {
            console.log("Dữ liệu đã được ghi lên Firebase Realtime Database.", THIETBI);
        })
        .catch((error) => {
            console.error("Lỗi khi ghi dữ liệu:", error);
        });
}

function updateTandH(temperature, humidity) {
  temperatureElement.textContent = `Nhiệt độ: ${temperature} °C`;
  humidityElement.textContent = `Độ ẩm: ${humidity}%`;
}
const den1Checkbox = document.getElementById('den1Checkbox');
const den2Checkbox = document.getElementById('den2Checkbox');
const den3Checkbox = document.getElementById('den3Checkbox');
const den4Checkbox = document.getElementById('den3Checkbox');
const quatCheckbox = document.getElementById('den3Checkbox');

// Hàm cập nhật trạng thái checkbox dựa trên biến den1 và các biến tương ứng
function checkbtn(D1,D2,D3,D4,QQ) {
    den1Checkbox.checked = (D1 === "TAT") ? false : true;
    den2Checkbox.checked = (D2 === "TAT") ? false : true;
    den3Checkbox.checked = (D3 === "TAT") ? false : true;
    den4Checkbox.checked = (D4 === "TAT") ? false : true;
    quatCheckbox.checked = (QQ === "TAT") ? false : true;
}


listenToData()