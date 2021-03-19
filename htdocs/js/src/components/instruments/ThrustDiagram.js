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
import {Gauge} from '../../ui/Gauge.js';

export class ThrustDiagram extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("thrust", this);
	}
	
	setSteam(dst)
	{
		App.api.command({component: "thrust", action: "setSteam", dst: dst});
	}
	
	buildClassName(name, active) {
		if(!active)
			return name+' inactive';
		return name+' active';
	}
	
	render() {
		if(this.state.thrust===undefined)
			return null;
		
		return (
			<div className="ThrustDiagram container">
				<div className="legend">Thrust diagram</div>
				
				<div className={this.buildClassName("thrust_out", (this.state.thrust.type=="ELECTRIC" && this.state.thrust["ELECTRIC"].rate>0) || (this.state.thrust.type=="MECHANICAL" && this.state.thrust["MECHANICAL"].rate>0))}></div>
				<div className={this.buildClassName("thrust_out_electric", this.state.thrust.type=="ELECTRIC")}></div>
				<div className={this.buildClassName("thrust_out_turbine", this.state.thrust.type=="MECHANICAL")}></div>
				<div className={this.buildClassName("electric_engine_thrust", this.state.thrust.type=="ELECTRIC")}></div>
				<div className={this.buildClassName("electric_engine", this.state.thrust["ELECTRIC"].rate>0)}>
					<div className="label">Electric engine</div>
				</div>
				<div className={this.buildClassName("electric_engine_battery", this.state.thrust["ELECTRIC"].battery_rate>0)}></div>
				<div className={this.buildClassName("battery", this.state.thrust["ELECTRIC"].battery_rate>0)}>
					<div className="label">Battery</div>
				</div>
				<div className={this.buildClassName("battery_generator", this.state.thrust["ELECTRIC"].battery_rate>0)}></div>
				<div className={this.buildClassName("generator", this.state.thrust["ELECTRIC"].battery_rate>0)}>
					<div className="label">Generator</div>
				</div>
				<div className={this.buildClassName("generator_steam", this.state.thrust.steam=="GENERATOR")}></div>
				<div className={this.buildClassName("steam_in_generator", this.state.thrust.steam=="GENERATOR")}></div>
				<div className={this.buildClassName("turbine_thrust", this.state.thrust.type=="MECHANICAL")}></div>
				<div className={this.buildClassName("turbine", this.state.thrust["MECHANICAL"].rate>0)}>
					<div className="label">Turbine</div>
				</div>
				<div className={this.buildClassName("turbine_steam", this.state.thrust.steam=="TURBINE")}></div>
				<div className={this.buildClassName("steam_in_turbine", this.state.thrust.steam=="TURBINE")}></div>
				<div className={this.buildClassName("steam_in", this.state.thrust.steam!="NONE")}></div>
			</div>
		);
	}
}
