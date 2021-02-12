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

export class Forces extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			proj: "x"
		};
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
		return Object.keys(this.props.forces).map((force_name) => {
			let proj = this.state.proj;
			
			let f = Object.assign({},this.props.forces[force_name]);
			
			let pf;
			if(proj=="x")
				pf = {x: f.y, y: -f.z, x0: f.y0, y0: -f.z0 };
			else if(proj=="z")
				pf = {x: f.y, y: f.x, x0: f.y0, y0: f.x0 };
			
			if(pf.x==0 && pf.y==0)
				return;
			
			let scale = 500000;
			if(scale==0)
				scale = 1;
			
			pf.x /= scale;
			pf.y /= scale;
			
			let text_x = pf.x0 + pf.x - 10;
			let text_y = pf.y>0?pf.y0 + pf.y + 7:pf.y0 + pf.y - 6;
			
			return (
				<React.Fragment key={force_name}>
					<line x1={pf.x0} y1={pf.y0} x2={pf.x0 + pf.x} y2={pf.y0 + pf.y} stroke="#ff0000" strokeWidth="1" markerEnd="url(#arrowhead)" />
					<text fontSize="2" x={text_x} y={text_y}>{force_name} {Math.round(f.norm/1000)} kN</text>
				</React.Fragment>
			);
		});
	}
	
	render() {
		return (
			<div className="Forces">
				<div>Projection : <span onClick={() => this.setState({proj: "x"}) }>x</span> <span onClick={() => this.setState({proj: "z"}) }>z</span></div>
				{ this.renderSVG() }
			</div>
		);
	}
}
