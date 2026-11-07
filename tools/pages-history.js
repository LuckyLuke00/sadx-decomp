// The History page's chart: tools/pages.py puts this script and the daily rows (#history-data) in the page. It
// draws the panels on one shared day axis, and zooms with the range buttons, a drag across the chart, or a
// double-click back to all days.
(() => {
  "use strict";
  const days = JSON.parse(document.getElementById("history-data").textContent);
  const chart = document.getElementById("chart");
  const rangeText = document.getElementById("range");
  const buttons = document.querySelectorAll(".chart-tools button");
  const NS = "http://www.w3.org/2000/svg";
  const LEFT = 58, RIGHT = 12, TITLE = 30, GAP = 16, AXIS = 26;
  const css = getComputedStyle(document.documentElement);
  const color = name => css.getPropertyValue(name).trim();
  const GOLD = color("--emblem"), BLUE = color("--sky-light"), CYAN = color("--cyan"), WHITE = "#ffffff";
  const share = (part, whole) => part / whole;
  const panels = [
    {title: "Functions", height: 140, percent: true, lines: [
      {value: d => share(d.decompiled, d.total), color: BLUE},
      {value: d => share(d.matched, d.total), color: GOLD, dash: "6 4"}]},
    {title: "Functions done a day", height: 120, bars: d => d.gain, zero: true, lines: [
      {value: d => d.pace, color: CYAN}]},
    {title: "Accuracy", height: 80, percent: true, lines: [
      {value: d => d.accuracy === null ? null : d.accuracy / 100, color: WHITE}]},
  ];
  let view = [0, days.length];  // the shown days, as day indices: day i covers [i, i + 1)
  let layout = null;

  const el = (name, attrs, parent) => {
    const node = document.createElementNS(NS, name);
    for (const key in attrs) node.setAttribute(key, attrs[key]);
    if (parent) parent.appendChild(node);
    return node;
  };
  const dayLabel = i => new Date(days[i].day + "T00:00:00Z").toLocaleDateString("en-US",
    {month: "short", day: "numeric", timeZone: "UTC"});
  const number = v => Math.round(v).toLocaleString("en-US");
  const percent = (v, digits) => (v * 100).toFixed(digits) + "%";

  function niceStep(span, count) {
    const raw = span / count, power = Math.pow(10, Math.floor(Math.log10(raw)));
    for (const step of [1, 2, 2.5, 5, 10]) if (step * power >= raw) return step * power;
    return 10 * power;
  }

  function yRange(panel, first, last) {
    const values = [];
    for (let i = first; i <= last; i++) {
      if (panel.bars) values.push(panel.bars(days[i]));
      for (const line of panel.lines) {
        const v = line.value(days[i]);
        if (v !== null) values.push(v);
      }
    }
    let lo = Math.min(...values), hi = Math.max(...values);
    if (panel.zero) lo = 0;
    const pad = Math.max((hi - lo) * 0.08, panel.percent ? 0.0005 : 1);
    if (!panel.zero) lo = Math.max(0, lo - pad);
    hi = panel.percent ? Math.min(1, hi + pad) : hi + pad;
    const step = niceStep(hi - lo, 3);
    return {lo: Math.floor(lo / step) * step, hi: Math.ceil(hi / step) * step, step};
  }

  function tickText(panel, v, step) {
    if (!panel.percent) return v >= 1000 ? number(v / 1000) + "k" : number(v);
    const digits = Math.max(0, Math.ceil(-Math.log10(step * 100)));
    return percent(v, digits);
  }

  function draw() {
    const width = chart.clientWidth;
    if (width < LEFT + RIGHT + 100) return;
    const plotRight = width - RIGHT;
    const x = i => LEFT + (i - view[0]) / (view[1] - view[0]) * (plotRight - LEFT);
    const first = Math.max(0, Math.floor(view[0])), last = Math.min(days.length - 1, Math.ceil(view[1]) - 1);
    let height = 0;
    for (const panel of panels) height += TITLE + panel.height + GAP;
    height += AXIS - GAP;
    const svg = el("svg", {viewBox: `0 0 ${width} ${height}`, height, role: "img",
      "aria-label": "Decompilation progress over time"});
    const defs = el("defs", {}, svg);
    const step = (plotRight - LEFT) / (view[1] - view[0]);
    let top = 0;
    layout = {x, first, last, width, plotRight, panels: []};
    panels.forEach((panel, index) => {
      const y0 = top + TITLE, y1 = y0 + panel.height;
      el("text", {x: 0, y: top + 15, class: "title"}, svg).textContent = panel.title;
      const range = yRange(panel, first, last);
      const y = v => y1 - (v - range.lo) / (range.hi - range.lo) * panel.height;
      for (let v = range.lo; v <= range.hi + range.step / 2; v += range.step) {
        el("line", {x1: LEFT, x2: plotRight, y1: y(v), y2: y(v), class: "grid"}, svg);
        el("text", {x: LEFT - 8, y: y(v) + 4, "text-anchor": "end"}, svg).textContent = tickText(panel, v, range.step);
      }
      if (step >= 6) for (let i = first + 1; i <= last; i++)
        el("line", {x1: x(i), x2: x(i), y1: y0, y2: y1, class: "day"}, svg);
      el("clipPath", {id: "clip" + index}, defs).appendChild(
        el("rect", {x: LEFT, y: y0 - 2, width: plotRight - LEFT, height: panel.height + 4}));
      const group = el("g", {"clip-path": `url(#clip${index})`}, svg);
      if (panel.bars) {
        const barWidth = Math.max(1, Math.min(step - 2, step * 0.7));
        for (let i = first; i <= last; i++) {
          const v = panel.bars(days[i]);
          if (v <= 0) continue;
          const h = y1 - y(v), r = Math.min(4, barWidth / 2, h);
          const left = x(i + 0.5) - barWidth / 2, right = left + barWidth, topY = y(v);
          const d = `M${left},${y1}V${topY + r}Q${left},${topY} ${left + r},${topY}` +
            `H${right - r}Q${right},${topY} ${right},${topY + r}V${y1}Z`;
          el("path", {fill: GOLD, "fill-opacity": 0.85, d}, group);
        }
      }
      for (const line of panel.lines) {
        const points = [];
        for (let i = Math.max(0, first - 1); i <= Math.min(days.length - 1, last + 1); i++) {
          const v = line.value(days[i]);
          if (v !== null) points.push(`${x(i + 0.5).toFixed(1)},${y(v).toFixed(1)}`);
        }
        el("polyline", {points: points.join(" "), fill: "none", stroke: line.color, "stroke-width": 2,
          "stroke-linejoin": "round", "stroke-dasharray": line.dash || "none"}, group);
      }
      layout.panels.push({y0, y1, y, panel});
      top = y1 + GAP;
    });
    const axisY = top - GAP + 18;
    const every = Math.max(1, Math.ceil(64 / step));
    for (let i = first; i <= last; i++) {
      if ((last - i) % every) continue;
      el("text", {x: x(i + 0.5), y: axisY, "text-anchor": "middle"}, svg).textContent = dayLabel(i);
    }
    layout.cross = el("line", {y1: 0, y2: top - GAP, class: "cross", visibility: "hidden"}, svg);
    layout.select = el("rect", {y: 0, height: top - GAP, class: "select", visibility: "hidden"}, svg);
    layout.overlay = el("rect", {x: LEFT, y: 0, width: plotRight - LEFT, height: top - GAP, fill: "transparent"}, svg);
    layout.tip = document.createElement("div");
    layout.tip.className = "tip";
    layout.tip.hidden = true;
    chart.replaceChildren(svg, layout.tip);
    hookPointer();
    rangeText.textContent = `${dayLabel(first)} to ${dayLabel(last)}`;
    const shown = last - first + 1;
    buttons.forEach(b => {
      const n = Number(b.dataset.days);
      b.setAttribute("aria-pressed", String(n ? n < days.length && shown === n && last === days.length - 1
        : first === 0 && last === days.length - 1));
    });
  }

  function dayAt(px) {
    const i = Math.floor(view[0] + (px - LEFT) / (layout.plotRight - LEFT) * (view[1] - view[0]));
    return Math.min(layout.last, Math.max(layout.first, i));
  }

  function showTip(px) {
    const i = dayAt(px), d = days[i], cx = layout.x(i + 0.5);
    layout.cross.setAttribute("x1", cx);
    layout.cross.setAttribute("x2", cx);
    layout.cross.setAttribute("visibility", "visible");
    const row = (c, label, value) =>
      `<div><span class="key" style="background:${c}"></span>${label}: <b>${value}</b></div>`;
    layout.tip.innerHTML = `<div><b>${dayLabel(i)}, ${d.day.slice(0, 4)}</b></div>` +
      row(BLUE, "Decompiled", `${number(d.decompiled)} (${percent(share(d.decompiled, d.total), 2)})`) +
      row(GOLD, "Done", `${number(d.matched)} (${percent(share(d.matched, d.total), 2)})`) +
      row(GOLD, "Done this day", `${number(d.gain)} functions`) +
      row(CYAN, "7-day average", `${number(d.pace)} functions a day`) +
      row(WHITE, "Accuracy", d.accuracy === null ? "none" : d.accuracy.toFixed(2) + "%");
    layout.tip.hidden = false;
    const tipWidth = layout.tip.offsetWidth;
    const left = cx + 14 + tipWidth > layout.width ? cx - 14 - tipWidth : cx + 14;
    layout.tip.style.left = Math.max(0, left) + "px";
    layout.tip.style.top = "8px";
  }

  function hideTip() {
    layout.cross.setAttribute("visibility", "hidden");
    layout.tip.hidden = true;
  }

  function hookPointer() {
    const overlay = layout.overlay;
    let start = null;
    const localX = event => event.clientX - chart.getBoundingClientRect().left;
    overlay.addEventListener("pointerdown", event => {
      start = localX(event);
      overlay.setPointerCapture(event.pointerId);
      showTip(start);
    });
    overlay.addEventListener("pointermove", event => {
      const px = Math.min(layout.plotRight, Math.max(LEFT, localX(event)));
      if (start !== null && Math.abs(px - start) > 4) {
        layout.select.setAttribute("x", Math.min(px, start));
        layout.select.setAttribute("width", Math.abs(px - start));
        layout.select.setAttribute("visibility", "visible");
        hideTip();
      } else if (start === null) showTip(px);
    });
    overlay.addEventListener("pointerup", event => {
      const px = Math.min(layout.plotRight, Math.max(LEFT, localX(event)));
      const from = start;
      start = null;
      layout.select.setAttribute("visibility", "hidden");
      if (from === null || Math.abs(px - from) <= 8) return;
      const a = dayAt(Math.min(px, from)), b = dayAt(Math.max(px, from));
      if (b > a) zoom(a, b + 1);
    });
    overlay.addEventListener("pointerleave", event => { if (event.pointerType === "mouse") hideTip(); });
    overlay.addEventListener("dblclick", () => zoom(0, days.length));
  }

  function zoom(a, b) {
    view = [a, b];
    draw();
  }

  buttons.forEach(button => button.addEventListener("click", () => {
    const n = Number(button.dataset.days);
    zoom(n ? Math.max(0, days.length - n) : 0, days.length);
  }));
  window.addEventListener("resize", draw);
  draw();
})();
