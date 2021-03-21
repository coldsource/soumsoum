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

export class Weighing extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("weighing", this);
	}
	
	formatInt(f) {
		f = Math.round(f);
		let s = f.toString();
		let rs = '';
		for(let i=0;i<s.length;i++)
		{
			if(i!=0 && (s.length-i)%3==0)
				rs += ' ';
			rs += s[i];
		}
		return rs.padStart(12, "\xa0");
	}
	
	render() {
		if(this.state.weighing===undefined)
			return null;
		
		const weighing = this.state.weighing;
		
		return (
			<div className="Weighing container">
				<div className="legend">Weighing</div>
				<div className="digital_display">
					<div className="row">
						Reference mass
						<span className="value">{this.formatInt(weighing.reference_mass)} Kg</span>
					</div>
					<div className="row">
						Reference net mass
						<span className="value">{this.formatInt(weighing.reference_net_mass)} Kg</span>
					</div>
					<div className="row">
						Current mass
						<span className="value">{this.formatInt(weighing.current_mass)} Kg</span>
					</div>
					<div className="row">
						Current net mass
						<span className="value">{this.formatInt(weighing.current_net_mass)} Kg</span>
					</div>
					<div className="row">
						Mass centering
						<span className="value">{weighing.mass_centering.toFixed(2)}</span>
					</div>
				</div>
			</div>
		);
	}
}
