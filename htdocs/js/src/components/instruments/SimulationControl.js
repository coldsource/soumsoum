 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {App} from '../base/App.js';

export class SimulationControl extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.keyDown = this.keyDown.bind(this);
		this.toggleSimulationRateLimit = this.toggleSimulationRateLimit.bind(this);
		
		App.registerComponent("simulation_control", this);
	}
	
	componentDidMount() {
		document.addEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	componentWillUnmount() {
		document.removeEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	keyDown(e) {
		if(e.key=="a")
			App.api.command({component: "simulation_control", action: "uncompressTime"});
		if(e.key=="z")
			App.api.command({component: "simulation_control", action: "compressTime"});
	}
	
	toggleSimulationRateLimit() {
		if(this.state.simulation_control.rate_limit)
			App.api.command({component: "simulation_control", action: "simulationRateLimitOff"});
		else
			App.api.command({component: "simulation_control", action: "simulationRateLimitOn"});
	}
	
	render() {
		if(this.state.simulation_control===undefined)
			return null;
		
		return (
			<div className="SimulationControl container">
				<div className="legend">Simulation control</div>
				Time compression : {this.state.simulation_control.time_compression.toFixed(0)} x
				<br />Simulation rate limiting : <span onClick={this.toggleSimulationRateLimit} className={this.state.simulation_control.rate_limit?"fa fa-check-square":"fa fa-square"}></span>
			</div>
		);
	}
}
