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
import {DivingPlane} from '../instruments/DivingPlane.js';

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
			<svg xmlns="http://www.w3.org/2000/svg" viewBox="-60 -20 120 40" style={{width:800, height:600}}>
				<defs>
					<marker id="arrowhead" markerWidth="5" markerHeight="3.5" refX="0" refY="1.75" orient="auto">
						<polygon points="0 0, 5 1.75, 0 3.5" />
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
			
			let scale = 500000;
			if(scale==0)
				scale = 1;
			
			f.y = f.y/scale;
			f.z = -f.z/scale;
			
			let text_x = f.y0 + f.y - 10;
			let text_y = f.z>0?f.z0 + f.z + 7:f.z0 + f.z - 6;
			
			return (
				<React.Fragment key={force_name}>
					<line x1={f.y0} y1={f.z0} x2={f.y0 + f.y} y2={f.z0 + f.z} stroke="#ff0000" strokeWidth="1" markerEnd="url(#arrowhead)" />
					<text fontSize="2" x={text_x} y={text_y}>{force_name} {Math.round(f.norm/1000)} kN</text>
				</React.Fragment>
			);
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
				<Thrust name="thrust" data={components.thrust} />
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
					<b>Attitude</b> : {this.radToDeg(data.attitude.x).toFixed(2)} {this.radToDeg(data.attitude.y).toFixed(2)} {this.radToDeg(data.attitude.z).toFixed(2)}
				</div>
				<div>
					<b>Air Tank</b> : { this.renderTank(data.air_tank) }
				</div>
				<div>
					{ this.renderSVG() }
				</div>
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
