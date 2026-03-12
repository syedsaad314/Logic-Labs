const Engine = {
    init() {
        this.canvas = document.getElementById('tactical-matrix');
        this.ctx = this.canvas.getContext('2d');
        this.resize();
        window.onresize = () => this.resize();

        this.hexes = [];
        this.initMatrix();
        this.startClock();
        this.setupTerminal();
        this.render();
        this.startStream();
    },

    resize() {
        this.canvas.width = this.canvas.offsetWidth;
        this.canvas.height = this.canvas.offsetHeight;
    },

    initMatrix() {
        const size = 25;
        const xStep = size * 1.5;
        const yStep = size * Math.sqrt(3);
        for(let x = 0; x < this.canvas.width + size; x += xStep) {
            for(let y = 0; y < this.canvas.height + size; y += yStep) {
                const xOffset = (Math.floor(y / yStep) % 2) * (size * 0.75);
                this.hexes.push({
                    x: x + xOffset, y: y, size: size,
                    active: Math.random() > 0.8,
                    pulse: Math.random() * Math.PI
                });
            }
        }
    },

    setupTerminal() {
        const input = document.getElementById('cmd-input');
        input.addEventListener('keydown', (e) => {
            if(e.key === 'Enter') {
                const cmd = input.value.toUpperCase();
                this.execute(cmd);
                input.value = '';
            }
        });
    },

    execute(cmd) {
        if(cmd === 'SCAN') {
            this.addLog("INITIATING SECTOR SCAN...", false);
            this.hexes.forEach(h => h.active = true);
        } else if(cmd === 'PURGE') {
            document.getElementById('threat-stream').innerHTML = '';
            this.addLog("STREAM_PURGE_SUCCESSFUL", true);
        } else {
            this.addLog(`ERR: UNKNOWN_CMD [${cmd}]`, true);
        }
    },

    addLog(msg, alert) {
        const stream = document.getElementById('threat-stream');
        const div = document.createElement('div');
        div.className = 'log-entry';
        div.innerHTML = `[${new Date().toLocaleTimeString()}] ${alert ? '<b>'+msg+'</b>' : msg}`;
        stream.prepend(div);
        if(stream.children.length > 10) stream.lastChild.remove();
    },

    render() {
        const { ctx, canvas } = this;
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        this.hexes.forEach(h => {
            ctx.beginPath();
            for (let i = 0; i < 6; i++) {
                ctx.lineTo(h.x + h.size * Math.cos(i * Math.PI / 3), 
                           h.y + h.size * Math.sin(i * Math.PI / 3));
            }
            ctx.closePath();
            
            const p = (Math.sin(Date.now()*0.002 + h.pulse) + 1) / 2;
            ctx.strokeStyle = h.active ? `rgba(0, 188, 212, ${0.1 + p*0.2})` : 'rgba(255,255,255,0.02)';
            ctx.stroke();
            if(h.active && p > 0.8) {
                ctx.fillStyle = 'rgba(0, 188, 212, 0.05)';
                ctx.fill();
            }
        });

        requestAnimationFrame(() => this.render());
    },

    startClock() {
        setInterval(() => {
            document.getElementById('clock').innerText = new Date().toLocaleTimeString();
        }, 1000);
    },

    startStream() {
        const t = ["MALWARE_DROP", "DDoS_BLOCK", "XSS_VECTOR", "SQL_INJECT"];
        setInterval(() => this.addLog(`${t[Math.floor(Math.random()*4)]} ATTEMPT FROM RU`, true), 4000);
    }
};

window.onload = () => Engine.init();