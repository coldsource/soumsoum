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
import {Ballast} from '../instruments/Ballast.js';
import {CompensatingTank} from '../instruments/CompensatingTank.js';
import {Thrust} from '../instruments/Thrust.js';
import {Rudder} from '../instruments/Rudder.js';
import {Speed} from '../instruments/Speed.js';
import {DivingPlane} from '../instruments/DivingPlane.js';
import {Forces} from '../instruments/Forces.js';
import {Compass} from '../instruments/Compass.js';
import {Map} from '../instruments/Map.js';
import {DepthMap} from '../instruments/DepthMap.js';

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
					this.components[name][i].setState({data: value});
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
				<Compass />
				<Thrust />
				<Rudder />
				<Speed />
				<Map />
				<DepthMap />
			</div>
		);
		return (
			<div>
				<Ballast name="ballast" data={components.ballast} />
				<CompensatingTank name="compensating_tank_back" data={components.compensating_tank_back} />
				<CompensatingTank name="compensating_tank_center" data={components.compensating_tank_center} />
				<CompensatingTank name="compensating_tank_front" data={components.compensating_tank_front} />
				<DivingPlane name="diving_plane" data={components.diving_plane} />
				<div>
					<b>Acceleration</b> : {data.acceleration.x.toFixed(2)} {data.acceleration.y.toFixed(2)} {data.acceleration.z.toFixed(2)}
				</div>
				<div>
					<b>Speed</b> : {data.speed.x.toFixed(2)} {data.speed.y.toFixed(2)} {data.speed.z.toFixed(2)}
				</div>
				<div>
					<b>Position</b> : {data.position.x.toFixed(2)} {data.position.y.toFixed(2)} {data.position.z.toFixed(2)}
				</div>
				<div>
					<b>Angular acceleration</b> : {this.radToDeg(data.angular_acceleration.x).toFixed(2)} {this.radToDeg(data.angular_acceleration.y).toFixed(2)} {this.radToDeg(data.angular_acceleration.z).toFixed(2)}
				</div>
				<div>
					<b>Angular speed</b> : {this.radToDeg(data.angular_speed.x).toFixed(2)} {this.radToDeg(data.angular_speed.y).toFixed(2)} {this.radToDeg(data.angular_speed.z).toFixed(2)}
				</div>
				<div>
					<b>Attitude</b> : {this.radToDeg(data.attitude.x).toFixed(2)} {this.radToDeg(data.attitude.y).toFixed(2)} {this.radToDeg(data.attitude.z).toFixed(2)}
				</div>
				<div>
					<b>Air Tank</b> : { this.renderTank(data.air_tank) }
				</div>
				<div>
					<Forces forces={this.state.data.forces} />
				</div>
				<DepthMap />
				<div style={{position: 'absolute', top: '0px', right: '0px', width: '800px', height: '1000px'}}>
					<div style={{position: 'relative', top: '0px', overflow: 'hidden'}}>{this.renderYAxis(data.position.y)}</div>
					<div style={{position: 'absolute', top: '240px', right: '0px', width: '800px', height: '900px', backgroundColor: '#bff2ff'}}></div>
					<div style={{position: 'absolute', top: (-data.position.z * 10)+'px'}}>
						<img style={{height: '240px', rotate:(-data.attitude.x)+'rad'}} src="images/submarine.png" />
					</div>
				</div>
			</div>
		);
	}
}

ReactDOM.render(<App />, document.querySelector('#content'));
