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

export class App extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			data: undefined
		};
		
		App.api = this.api = new SoumsoumAPI();
		this.api.connect(this);
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
	
	renderSVG() {
		return (
			<svg xmlns="http://www.w3.org/2000/svg" viewBox="-80 -10 160 320" style={{width:480, height:1280}}>
				<defs>
					<marker id="arrowhead" markerWidth="10" markerHeight="7" refX="0" refY="3.5" orient="auto">
						<polygon points="0 0, 10 3.5, 0 7" />
					</marker>
				</defs>
				{ this.renderSVGForces() }
			</svg>
		);
	}
	
	renderSVGForces() {
		return Object.keys(this.state.data.forces).map((force_name) => {
			let f = Object.assign({},this.state.data.forces[force_name]);
			
			if(f.x==0 && f.y==0 && f.z==0)
				return;
			
			f.z0 = -f.z0;
			
			let scale = f.norm<10000000?f.norm/10:1000000;
			if(scale==0)
				scale = 1;
			
			f.y = f.y/scale;
			f.z = -f.z/scale;
			return (
				<React.Fragment key={force_name}>
					<line x1={f.y0} y1={f.z0} x2={f.y0 + f.y} y2={f.z0 + f.z} stroke="#ff0000" strokeWidth="1" markerEnd="url(#arrowhead)" />
					<text fontSize="5" x={f.y0 + f.y + 5} y={f.z0 + f.z + 10}>{force_name} {Math.round(f.norm/1000)} kN</text>
				</React.Fragment>
			);
		});
	}
	
	render() {
		if(this.state.data===undefined)
			return null;
		
		let data = this.state.data;
		let components = data.components;
		return (
			<div>
				<Ballast name="ballast" data={components.ballast} />
				<CompensatingTank name="compensating_tank_back" data={components.compensating_tank_back} />
				<CompensatingTank name="compensating_tank_center" data={components.compensating_tank_center} />
				<CompensatingTank name="compensating_tank_front" data={components.compensating_tank_front} />
				<div>
					<b>Acceleration</b> : {data.acceleration.x} {data.acceleration.y} {data.acceleration.z}
				</div>
				<div>
					<b>Speed</b> : {data.speed.x} {data.speed.y} {data.speed.z}
				</div>
				<div>
					<b>Position</b> : {data.position.x} {data.position.y} {data.position.z}
				</div>
				<div>
					<b>Attitude</b> : {data.attitude.x} {data.attitude.y} {data.attitude.z}
				</div>
				<div>
					<b>Air Tank</b> : { this.renderTank(data.air_tank) }
				</div>
				<div>
					{ this.renderSVG() }
				</div>
				<div style={{position: 'absolute', top: '0px', right: '0px', width: '800px', height: '1000px'}}>
					<div style={{position: 'absolute', top: '240px', right: '0px', width: '800px', height: '900px', backgroundColor: '#bff2ff'}}></div>
					<div style={{position: 'absolute', top: (-data.position.z * 10)+'px', left: (data.position.y * 10)+'px'}}>
						<img style={{height: '240px', rotate:data.attitude.x+'rad'}} src="images/submarine.png" />
					</div>
				</div>
			</div>
		);
	}
}

ReactDOM.render(<App />, document.querySelector('#content'));
