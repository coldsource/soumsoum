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

export class AirController extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			ballast_open: false
		};
		
		this.toggleBallast = this.toggleBallast.bind(this);
		this.toggleAirPump = this.toggleAirPump.bind(this);
		this.toggleSurfaceFill = this.toggleSurfaceFill.bind(this);
		
		App.registerComponent("air_controller", this);
		App.registerComponent("ballast", this);
	}
	
	toggleSurfaceFill(e) {
		if(this.state.air_controller.surface_fill=="on")
			App.api.command({component: "air_controller", action: "surfaceFillOff"});
		else
			App.api.command({component: "air_controller", action: "surfaceFillOn"});
	}
	
	toggleBallast() {
		if(this.state.ballast.opened)
			App.api.command({component: "ballast", action: "close"});
		else
			App.api.command({component: "ballast", action: "open"});
	}
	
	toggleAirPump() {
		if(this.state.ballast.air_pump=="on")
			App.api.command({component: "ballast", action: "air_pump_off"});
		else
			App.api.command({component: "ballast", action: "air_pump_on"});
	}
	
	render() {
		if(this.state.ballast===undefined || this.state.air_controller===undefined)
			return null;
		
		return (
			<div className="AirController container">
				<div className="Ballast">
					<div className="legend">Air controller</div>
					<div className="drain" style={{display: this.state.ballast.opened?"block":"none"}}></div>
					<div className="external_shell">
						<div className="water" style={{top: (100-this.state.ballast.fill*100)+'%'}}></div>
						<div className="internal_shell">
							<span className={this.state.ballast.opened?"fa fa-toggle-off":"fa fa-toggle-on"} onClick={this.toggleBallast}></span>
						</div>
					</div>
					<div className="pressure">{this.state.ballast.pressure.toFixed(1)} BAR</div>
				</div>
				
				<div className="air_tank">{Math.round(this.state.air_controller.main_tank.air.pressure)} BAR</div>
				
				<div className="ballast_pipe">
					<img src="images/arrow.svg" />
					<span className={this.state.ballast.air_pump=="on"?"fa fa-toggle-on":"fa fa-toggle-off"} onClick={this.toggleAirPump}></span>
				</div>
				
				<div className="surface_pipe">
					<img src="images/arrow.svg" />
					<span className={this.state.air_controller.surface_fill=="on"?"fa fa-toggle-on":"fa fa-toggle-off"} onClick={this.toggleSurfaceFill}></span>
				</div>
			</div>
		);
	}
}
