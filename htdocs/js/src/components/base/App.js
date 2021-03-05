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

import {SoumsoumAPI} from '../../websockets/soumsoum_api.js';
import {AirController} from '../instruments/AirController.js';
import {CompensatingTank} from '../instruments/CompensatingTank.js';
import {Thrust} from '../instruments/Thrust.js';
import {ThrustElectric} from '../instruments/ThrustElectric.js';
import {ThrustMechanical} from '../instruments/ThrustMechanical.js';
import {ThrustSteam} from '../instruments/ThrustSteam.js';
import {ThrustSource} from '../instruments/ThrustSource.js';
import {ThrustTextIndicators} from '../instruments/ThrustTextIndicators.js';
import {Rudder} from '../instruments/Rudder.js';
import {Speed} from '../instruments/Speed.js';
import {Acceleration} from '../instruments/Acceleration.js';
import {CollisionDetection} from '../instruments/CollisionDetection.js';
import {DivingPlane} from '../instruments/DivingPlane.js';
import {Forces} from '../instruments/Forces.js';
import {Compass} from '../instruments/Compass.js';
import {DepthMeter} from '../instruments/DepthMeter.js';
import {AttitudeIndicator} from '../instruments/AttitudeIndicator.js';
import {PitchControl} from '../instruments/PitchControl.js';
import {DepthControlTank} from '../instruments/DepthControlTank.js';
import {Map} from '../instruments/Map.js';
import {DepthMap} from '../instruments/DepthMap.js';
import {TextIndicators} from '../instruments/TextIndicators.js';
import {SimulationControl} from '../instruments/SimulationControl.js';
import {Tabs} from '../../ui/Tabs.js';
import {Tab} from '../../ui/Tab.js';

export class App extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.components = {};
		
		App.instance = this;
		App.registerComponent = this.registerComponent;
		
		App.api = this.api = new SoumsoumAPI();
		
		this.api.connect(this);
	}
	
	handleData(data) {
		if(data===null)
			return;
		
		for(const [name, value] of Object.entries(data)) {
			if(this.components[name]!==undefined)
			{
				for(let i=0;i<this.components[name].length;i++)
				{
					let state = {};
					state[name] = value;
					this.components[name][i].setState(state);
				}
			}
		}
	}
	
	registerComponent(name, instance) {
		App.instance.register_component(name, instance);
	}
	
	register_component(name, instance) {
		if(this.components[name]===undefined)
			this.components[name] = [];
		
		this.components[name].push(instance);
	}
	
	radToDeg(rad)
	{
		return rad * (180/Math.PI);
	}
	
	renderTank(tank) {
		return Object.keys(tank).map((fluid_name) => { 
			let fluid = tank[fluid_name];
			return (<b key={fluid_name}>{fluid_name} {fluid.volume} {fluid.pressure}</b>);
		});
	}
	
	renderYAxis(y) {
		let yi = Math.floor(y / 10);
		let r = Math.round((yi - y / 10) * 100);
		let graduations = [];
		for(let i=0;i<8;i++)
		{
			let margin = i==0?r:0;
			graduations.push(<div key={i} style={{display: 'inline-block', width: '100px', borderLeft: '1px solid red', boxSizing: 'border-box', marginLeft: margin+'px'}}>{yi *10 + i*10}</div>);
		}
		return graduations;
	}
	
	radToDeg(a) {
		return a / Math.PI * 180;
	}
	
	render() {
		return (
			<div>
				<Tabs>
					<Tab title="Control">
						<div className="instruments_row">
							<SimulationControl />
							<Compass />
							<DepthMeter />
							<table><tbody>
								<tr>
									<td>
										<Thrust />
									</td>
									<td>
										<DivingPlane />
									</td>
								</tr>
								<tr>
									<td colSpan="2">
										<Rudder />
									</td>
								</tr>
							</tbody></table>
							<table><tbody>
								<tr>
									<td>
										<AttitudeIndicator />
									</td>
									<td>
										<TextIndicators />
									</td>
								</tr>
								<tr>
									<td>
										<Speed />
									</td>
									<td rowSpan="2">
										<CollisionDetection />
									</td>
								</tr>
								<tr>
									<td>
										<Acceleration />
									</td>
								</tr>
							</tbody></table>
						</div>
						<div className="instruments_row">
							<DepthMap />
						</div>
					</Tab>
					<Tab title="Buoyancy">
						<AirController />
						<PitchControl />
						<DepthControlTank />
					</Tab>
					<Tab title="Propulsion">
						<ThrustElectric />
						<ThrustMechanical />
						<ThrustSteam />
						<ThrustSource />
						<ThrustTextIndicators />
					</Tab>
					<Tab title="Map">
						<Map />
					</Tab>
					<Tab title="Forces">
						<Forces />
					</Tab>
				</Tabs>
			</div>
		);
	}
}

ReactDOM.render(<App />, document.querySelector('#content'));
