const checkboxes = document.querySelectorAll('input[type=checkbox]');

checkboxes.forEach((checkbox) => {
  checkbox.addEventListener('change', () => {
    const isChecked = checkbox.checked;
    const lightName = checkbox.parentNode.parentNode.querySelector('p').textContent;
    if (isChecked) {
      alert(`${lightName} is turned on`);
    } else {
      alert(`${lightName} is turned off`);
    }
  });
});
